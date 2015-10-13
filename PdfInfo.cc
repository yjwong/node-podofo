#include <node.h>
#include "PdfInfo.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Number;
using v8::Boolean;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfInfo::constructor_template;

PdfInfo::PdfInfo(PoDoFo::PdfInfo* obj) : _obj(obj) { }

PdfInfo::~PdfInfo() { }

void PdfInfo::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfInfo").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(8);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "GetAuthor", GetAuthor);
  Nan::SetPrototypeMethod(tpl, "GetCreator", GetCreator);
  Nan::SetPrototypeMethod(tpl, "GetKeywords", GetKeywords);
  Nan::SetPrototypeMethod(tpl, "GetSubject", GetSubject);
  Nan::SetPrototypeMethod(tpl, "GetTitle", GetTitle);
  Nan::SetPrototypeMethod(tpl, "GetProducer", GetProducer);
  Nan::SetPrototypeMethod(tpl, "GetTrapped", GetTrapped);

  constructor_template.Reset(tpl); 
  exports->Set(Nan::New("PdfInfo").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfInfo::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfInfo objects");
  }

  if (info.Length() < 1 || !info[0]->IsExternal()) {
    return Nan::ThrowTypeError("PdfInfo object cannot be created directly");
  }

  PdfInfo* pdfInfo = new PdfInfo(static_cast<PoDoFo::PdfInfo*>(
      External::Cast(*info[0])->Value()));
  pdfInfo->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfInfo::GetAuthor) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString author = obj->_obj->GetAuthor();
  info.GetReturnValue().Set(Nan::New<String>(author.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetCreator) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString creator = obj->_obj->GetCreator();
  info.GetReturnValue().Set(Nan::New<String>(creator.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetKeywords) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString keywords = obj->_obj->GetKeywords();
  info.GetReturnValue().Set(Nan::New<String>(keywords.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetSubject) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString subject = obj->_obj->GetSubject();
  info.GetReturnValue().Set(Nan::New<String>(subject.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetTitle) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString title = obj->_obj->GetTitle();
  info.GetReturnValue().Set(Nan::New<String>(title.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetProducer) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfString producer = obj->_obj->GetProducer();
  info.GetReturnValue().Set(Nan::New<String>(producer.GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfInfo::GetTrapped) {
  Nan::HandleScope scope;
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(info.This());
  PoDoFo::PdfName trapped = obj->_obj->GetTrapped();
  info.GetReturnValue().Set(Nan::New<String>(trapped.GetName()).ToLocalChecked());
}

