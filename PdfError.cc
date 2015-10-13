#include <node.h>
#include "PdfError.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfError::constructor_template;

PdfError::PdfError(PoDoFo::PdfError* obj) :
  _obj(new PoDoFo::PdfError(*obj)) { }

PdfError::~PdfError() { }

void PdfError::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfError").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(3);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "GetError", GetError);
  Nan::SetPrototypeMethod(tpl, "IsError", IsError);
  Nan::SetPrototypeMethod(tpl, "what", what);

  constructor_template.Reset(tpl); 
  exports->Set(Nan::New("PdfError").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfError::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfError objects");
  }

  if (info.Length() < 1 || !info[0]->IsExternal()) {
    return Nan::ThrowTypeError("PdfError object cannot be created directly");
  }

  PdfError* error = new PdfError(static_cast<PoDoFo::PdfError*>(
      External::Cast(*info[0])->Value()));
  error->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfError::GetError) {
  Nan::HandleScope scope;
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(info.This());
  info.GetReturnValue().Set(obj->_obj->GetError());
}

NAN_METHOD(PdfError::IsError) {
  Nan::HandleScope scope;
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsError() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfError::what) {
  Nan::HandleScope scope;
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(info.This());
  info.GetReturnValue().Set(Nan::New<String>(obj->_obj->what()).ToLocalChecked());
}

