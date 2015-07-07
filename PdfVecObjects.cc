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

Persistent<FunctionTemplate> PdfVecObjects::constructor_template;

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
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfVecObjects"));
  tpl->InstanceTemplate()->SetInternalFieldCount(3);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetSize", GetSize);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetObjectCount", GetObjectCount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ToArray", ToArray);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfVecObjects"), tpl->GetFunction());
}

NAN_METHOD(PdfVecObjects::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfVecObjects objects");
  }

  PdfVecObjects* objects;
  if (args.Length() == 1 && args[0]->IsExternal()) {
    objects = new PdfVecObjects(static_cast<PoDoFo::PdfVecObjects*>(
          External::Cast(*args[0])->Value()));
  } else {
    objects = new PdfVecObjects();
  }

  objects->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfVecObjects::GetSize) {
  NanScope();

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(args.This());
  size_t size = obj->_obj->GetSize();

  NanReturnValue(NanNew<Number>(size));
}

NAN_METHOD(PdfVecObjects::GetObjectCount) {
  NanScope();

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(args.This());
  size_t count = obj->_obj->GetObjectCount();

  NanReturnValue(NanNew<Number>(count));
}

NAN_METHOD(PdfVecObjects::ToArray) {
  NanScope();

  PdfVecObjects* obj = ObjectWrap::Unwrap<PdfVecObjects>(args.This());

  // Create JS array to contain wrapped instances of PdfObjects.
  Local<Array> arr = NanNew<Array>(obj->_obj->GetSize());
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  for (PoDoFo::PdfVecObjects::iterator it = obj->_obj->begin();
       it != obj->_obj->end(); ++it) {
    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { NanNew<External>(*it) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);
    arr->Set(std::distance(obj->_obj->begin(), it), newObj);
  }

  NanReturnValue(arr);
}

