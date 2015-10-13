#include <node.h>
#include "PdfObject.h"
#include "PdfVecObjects.h"

using v8::Handle;
using v8::Value;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Function;
using v8::Number;
using v8::Array;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfVecObjects::constructor_template;

PdfVecObjects::PdfVecObjects() :
  _obj(new PoDoFo::PdfVecObjects()),
  _objFromElsewhere(false) {
}

PdfVecObjects::PdfVecObjects(PoDoFo::PdfVecObjects* obj) :
  _obj(obj),
  _objFromElsewhere(true) { }

PdfVecObjects::~PdfVecObjects() {
  if (!_objFromElsewhere) { delete _obj; }
}

PoDoFo::PdfVecObjects* PdfVecObjects::Unwrap() {
  return _obj;
}

void PdfVecObjects::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfVecObjects").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(3);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "GetSize", GetSize);
  Nan::SetPrototypeMethod(tpl, "GetObjectCount", GetObjectCount);
  Nan::SetPrototypeMethod(tpl, "ToArray", ToArray);

  constructor_template.Reset(tpl);
  exports->Set(Nan::New("PdfVecObjects").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfVecObjects::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfVecObjects objects");
  }

  PdfVecObjects* objects;
  if (info.Length() == 1 && info[0]->IsExternal()) {
    objects = new PdfVecObjects(static_cast<PoDoFo::PdfVecObjects*>(
          External::Cast(*info[0])->Value()));
  } else {
    objects = new PdfVecObjects();
  }

  objects->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfVecObjects::GetSize) {
  Nan::HandleScope scope;

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(info.This());
  size_t size = obj->_obj->GetSize();

  info.GetReturnValue().Set(Nan::New<Number>(size));
}

NAN_METHOD(PdfVecObjects::GetObjectCount) {
  Nan::HandleScope scope;

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(info.This());
  size_t count = obj->_obj->GetObjectCount();

  info.GetReturnValue().Set(Nan::New<Number>(count));
}

NAN_METHOD(PdfVecObjects::ToArray) {
  Nan::HandleScope scope;

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(info.This());

  // Create JS array to contain wrapped instances of PdfObjects.
  Local<Array> arr = Nan::New<Array>(obj->_obj->GetSize());
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  for (PoDoFo::PdfVecObjects::iterator it = obj->_obj->begin();
       it != obj->_obj->end(); ++it) {
    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { Nan::New<External>(*it) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);
    arr->Set(std::distance(obj->_obj->begin(), it), newObj);
  }

  info.GetReturnValue().Set(arr);
}

