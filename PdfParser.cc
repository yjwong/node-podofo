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

Persistent<FunctionTemplate> PdfParser::constructor_template;

PdfParser::PdfParser(PdfVecObjects* pVecObjects) {
  _obj = new PoDoFo::PdfParser(pVecObjects->Unwrap());
  _filename = NULL;
}

PdfParser::~PdfParser() {
  delete _obj;
  if (_filename != NULL) { delete _filename; }
}

void PdfParser::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfParser"));
  tpl->InstanceTemplate()->SetInternalFieldCount(5);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "ParseFile", ParseFile);
  NODE_SET_PROTOTYPE_METHOD(tpl, "QuickEncryptedCheck", QuickEncryptedCheck);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetNumberOfIncrementalUpdates", GetNumberOfIncrementalUpdates);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetPdfVersionString", GetPdfVersionString);
  
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfParser"), tpl->GetFunction());
}

NAN_METHOD(PdfParser::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfParser objects");
  }

  if (args.Length() < 1) {
    return NanThrowTypeError("PdfParser requires at least 1 argument");
  }

  PdfVecObjects* pVecObjects = ObjectWrap::Unwrap<PdfVecObjects>(args[0]->ToObject());

  PdfParser* parser = new PdfParser(pVecObjects);
  parser->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfParser::ParseFile) {
  NanScope();

  if (args.Length() < 1) {
    return NanThrowTypeError("ParseFile requires at least 1 argument");
  }

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(args.This());
  Local<String> filename = args[0]->ToString();
  Local<Boolean> loadOnDemand = args[1]->IsUndefined() ? NanTrue() : args[1]->ToBoolean();

  obj->_filename = new NanUtf8String(filename);
  obj->_obj->ParseFile(obj->_filename->operator*(), loadOnDemand->Value());
  NanReturnUndefined();
}

NAN_METHOD(PdfParser::QuickEncryptedCheck) {
  NanScope();

  if (args.Length() < 1) {
    return NanThrowTypeError("QuickEncryptedCheck requires at least 1 argument");
  }

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(args.This());
  Local<String> filename = args[0]->ToString();

  NanUtf8String* charFilename = new NanUtf8String(filename);
  bool encrypted = obj->_obj->QuickEncryptedCheck(charFilename->operator*());

  NanReturnValue(encrypted ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfParser::GetNumberOfIncrementalUpdates) {
  NanScope();

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(args.This());
  int updates = obj->_obj->GetNumberOfIncrementalUpdates();

  NanReturnValue(NanNew<Number>(updates));
}

NAN_METHOD(PdfParser::GetPdfVersionString) {
  NanScope();

  PdfParser* obj = ObjectWrap::Unwrap<PdfParser>(args.This());
  const char* charString = obj->_obj->GetPdfVersionString();
  Local<String> string = String::NewFromUtf8(Isolate::GetCurrent(), charString,
      String::kNormalString, strlen(charString));

  NanReturnValue(string);
}

