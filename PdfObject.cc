#include <node.h>
#include "PdfVariant.h"
#include "PdfObject.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Number;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfObject::constructor_template;

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
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->Inherit(Nan::New(PdfVariant::constructor_template));
  tpl->SetClassName(Nan::New("PdfObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  //NODE_SET_PROTOTYPE_METHOD(tpl, "GetSize", GetSize);

  constructor_template.Reset(tpl); 
  exports->Set(Nan::New("PdfObject").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfObject::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfObject objects");
  }

  PdfObject* objects;
  if (info.Length() == 1 && info[0]->IsExternal()) {
    objects = new PdfObject(static_cast<PoDoFo::PdfObject*>(
          External::Cast(*info[0])->Value()));
  } else {
    objects = new PdfObject();
  }

  objects->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

