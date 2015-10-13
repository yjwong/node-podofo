#include <node.h>
#include "PdfParser.h"

using v8::Handle;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::String;
using v8::Boolean;
using v8::Number;

Nan::Persistent<FunctionTemplate> PdfParser::constructor_template;

PdfParser::PdfParser(PdfVecObjects* pVecObjects) {
  _obj = new PoDoFo::PdfParser(pVecObjects->Unwrap());
  _filename = NULL;
}

PdfParser::~PdfParser() {
  delete _obj;
  if (_filename != NULL) { delete _filename; }
}

void PdfParser::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfParser").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(5);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "ParseFile", ParseFile);
  Nan::SetPrototypeMethod(tpl, "QuickEncryptedCheck", QuickEncryptedCheck);
  Nan::SetPrototypeMethod(tpl, "GetNumberOfIncrementalUpdates", GetNumberOfIncrementalUpdates);
  Nan::SetPrototypeMethod(tpl, "GetPdfVersionString", GetPdfVersionString);
  
  constructor_template.Reset(tpl);
  exports->Set(Nan::New("PdfParser").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfParser::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfParser objects");
  }

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("PdfParser requires at least 1 argument");
  }

  PdfVecObjects* pVecObjects = ObjectWrap::Unwrap<PdfVecObjects>(info[0]->ToObject());

  PdfParser* parser = new PdfParser(pVecObjects);
  parser->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfParser::ParseFile) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("ParseFile requires at least 1 argument");
  }

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(info.This());
  Local<String> filename = info[0]->ToString();
  Local<Boolean> loadOnDemand = info[1]->IsUndefined() ? Nan::True() : info[1]->ToBoolean();

  obj->_filename = new Nan::Utf8String(filename);
  obj->_obj->ParseFile(obj->_filename->operator*(), loadOnDemand->Value());
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfParser::QuickEncryptedCheck) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowTypeError("QuickEncryptedCheck requires at least 1 argument");
  }

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(info.This());
  Local<String> filename = info[0]->ToString();

  Nan::Utf8String* charFilename = new Nan::Utf8String(filename);
  bool encrypted = obj->_obj->QuickEncryptedCheck(charFilename->operator*());

  info.GetReturnValue().Set(encrypted ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfParser::GetNumberOfIncrementalUpdates) {
  Nan::HandleScope scope;

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(info.This());
  int updates = obj->_obj->GetNumberOfIncrementalUpdates();

  info.GetReturnValue().Set(Nan::New<Number>(updates));
}

NAN_METHOD(PdfParser::GetPdfVersionString) {
  Nan::HandleScope scope;

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(info.This());
  const char* charString = obj->_obj->GetPdfVersionString();
  Local<String> string = String::NewFromUtf8(Isolate::GetCurrent(), charString,
      String::kNormalString, strlen(charString));

  info.GetReturnValue().Set(string);
}

