#include <node.h>
#include "PdfPage.h"
#include "PdfVariant.h"
#include "PdfContentsTokenizer.h"

using v8::Handle;
using v8::Value;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfContentsTokenizer::constructor_template;

PdfContentsTokenizer::PdfContentsTokenizer(PoDoFo::PdfCanvas* pCanvas) :
  _obj(new PoDoFo::PdfContentsTokenizer(pCanvas)) { }

PdfContentsTokenizer::~PdfContentsTokenizer() { }

void PdfContentsTokenizer::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfContentsTokenizer").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "ReadNext", ReadNext);

  constructor_template.Reset(tpl);
  exports->Set(Nan::New("PdfContentsTokenizer").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfContentsTokenizer::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfContentsTokenizer objects");
  }

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("PdfContentsTokenizer object cannot be created directly");
  }

  PdfContentsTokenizer* tokenizer;
  if (info[0]->IsExternal()) {
    tokenizer = new PdfContentsTokenizer(static_cast<PoDoFo::PdfCanvas*>(
          External::Cast(*info[0])->Value()));
  } else if (info[0]->IsObject()) {
    Local<Object> canvasObj = info[0]->ToObject();
    PdfPage* canvas = ObjectWrap::Unwrap<PdfPage>(canvasObj);
    tokenizer = new PdfContentsTokenizer(canvas->Unwrap());
  } else {
    return Nan::ThrowTypeError("First argument must be a PdfCanvas object");
  }

  tokenizer->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfContentsTokenizer::ReadNext) {
  Nan::HandleScope scope;

  PdfContentsTokenizer* obj = ObjectWrap::Unwrap<PdfContentsTokenizer>(info.This());

  PoDoFo::EPdfContentsType type;
  const char* keyword;
  PoDoFo::PdfVariant* variant = new PoDoFo::PdfVariant();

  bool retval = obj->_obj->ReadNext(type, keyword, *variant);
  if (!retval) {
    info.GetReturnValue().Set(Nan::False());
  } else {
    Local<Object> retObj = Nan::New<Object>();
    retObj->Set(Nan::New<String>("type").ToLocalChecked(), Nan::New<Number>(type));

    switch (type) {
    case PoDoFo::ePdfContentsType_Keyword:
      retObj->Set(Nan::New<String>("keyword").ToLocalChecked(),
          Nan::New<String>(keyword).ToLocalChecked());
      break;
    case PoDoFo::ePdfContentsType_Variant:
    case PoDoFo::ePdfContentsType_ImageData:
      // Construct the PdfVariant object.
      Local<FunctionTemplate> tpl = Nan::New(PdfVariant::constructor_template);
      Local<Function> func = tpl->GetFunction();
      Handle<Value> newFuncArgs[] = { Nan::New<External>(variant) };
      Local<Object> newObj = func->NewInstance(1, newFuncArgs);
      retObj->Set(Nan::New<String>("variant").ToLocalChecked(), newObj);
      break;
    }
    
    info.GetReturnValue().Set(retObj);
  }
}

