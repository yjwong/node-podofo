#include <node.h>
#include "PdfVariant.h"
#include "PdfObject.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Number;
using v8::External;

Persistent<FunctionTemplate> PdfObject::constructor_template;

PdfObject::PdfObject() :
  _obj(new PoDoFo::PdfObject()),
  _objFromElsewhere(false) {
}

PdfObject::PdfObject(PoDoFo::PdfObject* obj) :
  _obj(obj),
  _objFromElsewhere(true) { }

PdfObject::~PdfObject() {
  if (!_objFromElsewhere) { delete _obj; }
}

void PdfObject::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->Inherit(NanNew(PdfVariant::constructor_template));
  tpl->SetClassName(NanNew("PdfObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  //NODE_SET_PROTOTYPE_METHOD(tpl, "GetSize", GetSize);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfObject"), tpl->GetFunction());
}

NAN_METHOD(PdfObject::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfObject objects");
  }

  PdfObject* objects;
  if (args.Length() == 1 && args[0]->IsExternal()) {
    objects = new PdfObject(static_cast<PoDoFo::PdfObject*>(
          External::Cast(*args[0])->Value()));
  } else {
    objects = new PdfObject();
  }

  objects->Wrap(args.This());
  NanReturnValue(args.This());
}

