#include <node.h>
#include "PdfObject.h"
#include "PdfPage.h"

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
using v8::Value;

Persistent<FunctionTemplate> PdfPage::constructor_template;

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
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfPage"));
  tpl->InstanceTemplate()->SetInternalFieldCount(5);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetPageNumber", GetPageNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetContents", GetContents);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetResources", GetContents);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetObject", GetObject);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfPage"), tpl->GetFunction());
}

NAN_METHOD(PdfPage::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfPage objects");
  }

  if (args.Length() == 1 && !args[0]->IsExternal()) {
    return NanThrowTypeError("PdfPage cannot be created directly");
  }

  PdfPage* page = new PdfPage(static_cast<PoDoFo::PdfPage*>(
          External::Cast(*args[0])->Value()));
  page->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfPage::GetPageNumber) {
  NanScope();
  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(args.This());
  NanReturnValue(NanNew<Number>(obj->_obj->GetPageNumber()));
}

NAN_METHOD(PdfPage::GetContents) {
  NanScope();

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(args.This());
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { NanNew<External>(obj->_obj->GetContents()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  NanReturnValue(newObj);
}

NAN_METHOD(PdfPage::GetResources) {
  NanScope();

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(args.This());
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { NanNew<External>(obj->_obj->GetResources()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  NanReturnValue(newObj);
}

NAN_METHOD(PdfPage::GetObject) {
  NanScope();

  PdfPage* obj = ObjectWrap::Unwrap<PdfPage>(args.This());
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { NanNew<External>(obj->_obj->GetObject()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  NanReturnValue(newObj);
}

