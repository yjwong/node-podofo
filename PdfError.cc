#include <node.h>
#include "PdfError.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;

Persistent<FunctionTemplate> PdfError::constructor_template;

PdfError::PdfError(PoDoFo::PdfError* obj) :
  _obj(new PoDoFo::PdfError(*obj)) { }

PdfError::~PdfError() { }

void PdfError::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfError"));
  tpl->InstanceTemplate()->SetInternalFieldCount(3);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetError", GetError);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsError", IsError);
  NODE_SET_PROTOTYPE_METHOD(tpl, "what", what);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfError"), tpl->GetFunction());
}

NAN_METHOD(PdfError::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfError objects");
  }

  if (args.Length() < 1 || !args[0]->IsExternal()) {
    return NanThrowTypeError("PdfError object cannot be created directly");
  }

  PdfError* info = new PdfError(static_cast<PoDoFo::PdfError*>(
      External::Cast(*args[0])->Value()));
  info->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfError::GetError) {
  NanScope();
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(args.This());
  NanReturnValue(obj->_obj->GetError());
}

NAN_METHOD(PdfError::IsError) {
  NanScope();
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(args.This());
  NanReturnValue(obj->_obj->IsError() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfError::what) {
  NanScope();
  PdfError* obj = ObjectWrap::Unwrap<PdfError>(args.This());
  NanReturnValue(NanNew<String>(obj->_obj->what()));
}

