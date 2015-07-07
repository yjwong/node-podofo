#include <node.h>
#include "PdfError.h"
#include "PdfInfo.h"
#include "PdfPage.h"
#include "PdfVecObjects.h"
#include "PdfMemDocument.h"

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

Persistent<FunctionTemplate> PdfMemDocument::constructor_template;

PdfMemDocument::PdfMemDocument() {
	_obj = new PoDoFo::PdfMemDocument();
}

PdfMemDocument::~PdfMemDocument() {
	delete _obj;
}

void PdfMemDocument::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfMemDocument"));
  tpl->InstanceTemplate()->SetInternalFieldCount(4);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "Load", Load);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetObjects", GetObjects);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetInfo", GetInfo);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetPageCount", GetPageCount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetPage", GetPage);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfMemDocument"), tpl->GetFunction());
}

NAN_METHOD(PdfMemDocument::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfMemDocument objects");
  }

  PdfMemDocument* objects = new PdfMemDocument();
  objects->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfMemDocument::Load) {
  NanScope();

  if (args.Length() < 1) {
    return NanThrowTypeError("Load requires at least 1 argument");
  }

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(args.This());
  Local<String> filename = args[0]->ToString();

  try {
    NanUtf8String* charFilename = new NanUtf8String(filename);
    obj->_obj->Load(charFilename->operator*());
  } catch (PoDoFo::PdfError& e) {
    Local<FunctionTemplate> errTpl = NanNew(PdfError::constructor_template);
    Local<Function> errFunc = errTpl->GetFunction();
    Handle<Value> errFuncArgs[] = { NanNew<External>(&e) };
    Local<Object> errObj = errFunc->NewInstance(1, errFuncArgs);
    return NanThrowError(errObj);
  }

  NanReturnUndefined();
}

NAN_METHOD(PdfMemDocument::GetObjects) {
  NanScope();

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(args.This());
  Local<FunctionTemplate> tpl = NanNew(PdfVecObjects::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { NanNew<External>(&obj->_obj->GetObjects()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  NanReturnValue(newObj);
}

NAN_METHOD(PdfMemDocument::GetInfo) {
  NanScope();

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(args.This());
  Local<FunctionTemplate> tpl = NanNew(PdfInfo::constructor_template);
  Local<Function> func = tpl->GetFunction();

  Handle<Value> newFuncArgs[] = { NanNew<External>(obj->_obj->GetInfo()) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);

  NanReturnValue(newObj);
}

NAN_METHOD(PdfMemDocument::GetPageCount) {
  NanScope();
  
  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(args.This());
  int count = obj->_obj->GetPageCount();

  NanReturnValue(NanNew<Number>(count));
}

NAN_METHOD(PdfMemDocument::GetPage) {
  NanScope();

  if (args.Length() < 1) {
    return NanThrowTypeError("GetPage requires at least 1 argument");
  }

  PdfMemDocument* obj = ObjectWrap::Unwrap<PdfMemDocument>(args.This());
  Local<Number> index = args[0]->ToNumber();

  Local<FunctionTemplate> tpl = NanNew(PdfPage::constructor_template);
  Local<Function> func = tpl->GetFunction();

  PoDoFo::PdfPage* page = obj->_obj->GetPage(index->Int32Value());
  Handle<Value> newFuncArgs[] = { NanNew<External>(page) };
  Local<Object> newObj = func->NewInstance(1, newFuncArgs);
  
  NanReturnValue(newObj);
}

