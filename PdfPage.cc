#include <node.h>
#include "PdfObject.h"
#include "PdfPage.h"

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

Nan::Persistent<FunctionTemplate> PdfPage::constructor_template;

PdfPage::PdfPage(PoDoFo::PdfPage* obj) :
  _obj(obj),
  _objFromElsewhere(true) { }

PdfPage::~PdfPage() {
	if (!_objFromElsewhere) { delete _obj; }
}

PoDoFo::PdfPage* PdfPage::Unwrap() {
  return _obj;
}

void PdfPage::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfPage").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(5);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "GetPageNumber", GetPageNumber);
  Nan::SetPrototypeMethod(tpl, "GetContents", GetContents);
  Nan::SetPrototypeMethod(tpl, "GetResources", GetContents);
  Nan::SetPrototypeMethod(tpl, "GetObject", GetObject);

  constructor_template.Reset(tpl); 
  exports->Set(Nan::New("PdfPage").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfPage::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfPage objects");
  }

  if (info.Length() == 1 && !info[0]->IsExternal()) {
    return Nan::ThrowTypeError("PdfPage cannot be created directly");
  }

  PdfPage* page = new PdfPage(static_cast<PoDoFo::PdfPage*>(
          External::Cast(*info[0])->Value()));
  page->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfPage::GetPageNumber) {
  Nan::HandleScope scope;
  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(obj->_obj->GetPageNumber()));
}

NAN_METHOD(PdfPage::GetContents) {
  Nan::HandleScope scope;

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(info.This());
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { Nan::New<External>(obj->_obj->GetContents()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}

NAN_METHOD(PdfPage::GetResources) {
  Nan::HandleScope scope;

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(info.This());
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { Nan::New<External>(obj->_obj->GetResources()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}

NAN_METHOD(PdfPage::GetObject) {
  Nan::HandleScope scope;

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(info.This());
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { Nan::New<External>(obj->_obj->GetObject()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  info.GetReturnValue().Set(newObj);
}

