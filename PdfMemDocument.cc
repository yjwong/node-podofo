#include <node.h>
#include "PdfError.h"
#include "PdfInfo.h"
#include "PdfPage.h"
#include "PdfVecObjects.h"
#include "PdfMemDocument.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;
using v8::Value;

Nan::Persistent<FunctionTemplate> PdfMemDocument::constructor_template;

PdfMemDocument::PdfMemDocument() {
	_obj = new PoDoFo::PdfMemDocument();
}

PdfMemDocument::~PdfMemDocument() {
  delete _obj;
}

void PdfMemDocument::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfMemDocument").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(4);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "Load", Load);
  Nan::SetPrototypeMethod(tpl, "GetObjects", GetObjects);
  Nan::SetPrototypeMethod(tpl, "GetInfo", GetInfo);
  Nan::SetPrototypeMethod(tpl, "GetPageCount", GetPageCount);
  Nan::SetPrototypeMethod(tpl, "GetPage", GetPage);
  Nan::SetPrototypeMethod(tpl, "GetPdfVersion", GetPdfVersion);

  constructor_template.Reset(tpl);
  exports->Set(Nan::New("PdfMemDocument").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfMemDocument::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfMemDocument objects");
  }

  if(info.Length() && info[0]->IsBoolean() && info[0]->IsTrue() ){
    PoDoFo::PdfError::EnableDebug(true);
	  PoDoFo::PdfError::EnableLogging(true);
  }else{
    PoDoFo::PdfError::EnableDebug(false);
	  PoDoFo::PdfError::EnableLogging(false);
  }

  PdfMemDocument* objects = new PdfMemDocument();
  objects->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfMemDocument::Load) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("Load requires at least 1 argument");
  }

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  Local<String> filename = info[0]->ToString();

  try {
    Nan::Utf8String* charFilename = new Nan::Utf8String(filename);
    obj->_obj->Load(charFilename->operator*());
  } catch (PoDoFo::PdfError& e) {
    Local<FunctionTemplate> errTpl = Nan::New(PdfError::constructor_template);
    Local<Function> errFunc = errTpl->GetFunction();
    Handle<Value> errFuncArgs[] = { Nan::New<External>(&e) };
    Local<Value> errObj = errFunc->NewInstance(1, errFuncArgs);
    Nan::ThrowError(errObj);
  }

  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfMemDocument::GetObjects) {
  Nan::HandleScope scope;

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  Local<FunctionTemplate> tpl = Nan::New(PdfVecObjects::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { Nan::New<External>(&obj->_obj->GetObjects()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}

NAN_METHOD(PdfMemDocument::GetInfo) {
  Nan::HandleScope scope;

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  Local<FunctionTemplate> tpl = Nan::New(PdfInfo::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { Nan::New<External>(obj->_obj->GetInfo()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}

NAN_METHOD(PdfMemDocument::GetPageCount) {
  Nan::HandleScope scope;

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  int count = obj->_obj->GetPageCount();

  info.GetReturnValue().Set(Nan::New<Number>(count));
}

NAN_METHOD(PdfMemDocument::GetPdfVersion) {
  Nan::HandleScope scope;

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  int pdfVersion = obj->_obj->GetPdfVersion();

  info.GetReturnValue().Set(Nan::New<Number>(pdfVersion));
}

NAN_METHOD(PdfMemDocument::GetPage) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("GetPage requires at least 1 argument");
  }

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(info.This());
  Local<Number> index = info[0]->ToNumber();

  Local<FunctionTemplate> tpl = Nan::New(PdfPage::constructor_template);
  Local<Function> func = tpl->GetFunction();

  PoDoFo::PdfPage* page = obj->_obj->GetPage(index->Int32Value());
  Handle<Value> newFuncArgs[] = { Nan::New<External>(page) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}
