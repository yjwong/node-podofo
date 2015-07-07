#include <node.h>
#include "PdfPage.h"
#include "PdfVariant.h"
#include "PdfContentsTokenizer.h"

using v8::Handle;
using v8::Value;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;

Persistent<FunctionTemplate> PdfContentsTokenizer::constructor_template;

PdfContentsTokenizer::PdfContentsTokenizer(PoDoFo::PdfCanvas* pCanvas) :
  _obj(new PoDoFo::PdfContentsTokenizer(pCanvas)) { }

PdfContentsTokenizer::~PdfContentsTokenizer() { }

void PdfContentsTokenizer::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfContentsTokenizer"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "ReadNext", ReadNext);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfContentsTokenizer"), tpl->GetFunction());
}

NAN_METHOD(PdfContentsTokenizer::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfContentsTokenizer objects");
  }

  if (args.Length() < 1) {
    return NanThrowTypeError("PdfContentsTokenizer object cannot be created directly");
  }

  PdfContentsTokenizer* info;
  if (args[0]->IsExternal()) {
    info = new PdfContentsTokenizer(static_cast<PoDoFo::PdfCanvas*>(
          External::Cast(*args[0])->Value()));
  } else if (args[0]->IsObject()) {
    Local<Object> canvasObj = args[0]->ToObject();
    PdfPage* canvas = ObjectWrap::Unwrap<PdfPage>(canvasObj);
    info = new PdfContentsTokenizer(canvas->Unwrap());
  } else {
    return NanThrowTypeError("First argument must be a PdfCanvas object");
  }

  info->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfContentsTokenizer::ReadNext) {
  NanScope();

  PdfContentsTokenizer* obj = ObjectWrap::Unwrap<PdfContentsTokenizer>(args.This());

  PoDoFo::EPdfContentsType type;
  const char* keyword;
  PoDoFo::PdfVariant* variant = new PoDoFo::PdfVariant();

  bool retval = obj->_obj->ReadNext(type, keyword, *variant);
  if (!retval) {
    NanReturnValue(NanFalse());
  } else {
    Local<Object> retObj = NanNew<Object>();
    retObj->Set(NanNew<String>("type"), NanNew<Number>(type));

    switch (type) {
    case PoDoFo::ePdfContentsType_Keyword:
      retObj->Set(NanNew<String>("keyword"), NanNew<String>(keyword));
      break;
    case PoDoFo::ePdfContentsType_Variant:
    case PoDoFo::ePdfContentsType_ImageData:
      // Construct the PdfVariant object.
      Local<FunctionTemplate> tpl = NanNew(PdfVariant::constructor_template);
      Local<Function> func = tpl->GetFunction();
      Handle<Value> newFuncArgs[] = { NanNew<External>(variant) };
      Local<Object> newObj = func->NewInstance(1, newFuncArgs);
      retObj->Set(NanNew<String>("variant"), newObj);
      break;
    }
    
    NanReturnValue(retObj);
  }
}

