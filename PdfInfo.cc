#include <node.h>
#include "PdfInfo.h"

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

Persistent<FunctionTemplate> PdfInfo::constructor_template;

PdfInfo::PdfInfo(PoDoFo::PdfInfo* obj) : _obj(obj) { }

PdfInfo::~PdfInfo() { }

void PdfInfo::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfInfo"));
  tpl->InstanceTemplate()->SetInternalFieldCount(8);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetAuthor", GetAuthor);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetCreator", GetCreator);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetKeywords", GetKeywords);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetSubject", GetSubject);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetTitle", GetTitle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetProducer", GetProducer);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetTrapped", GetTrapped);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfInfo"), tpl->GetFunction());
}

NAN_METHOD(PdfInfo::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfInfo objects");
  }

  if (args.Length() < 1 || !args[0]->IsExternal()) {
    return NanThrowTypeError("PdfInfo object cannot be created directly");
  }

  PdfInfo* info = new PdfInfo(static_cast<PoDoFo::PdfInfo*>(
      External::Cast(*args[0])->Value()));
  info->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfInfo::GetAuthor) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString author = obj->_obj->GetAuthor();
  NanReturnValue(NanNew<String>(author.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetCreator) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString creator = obj->_obj->GetCreator();
  NanReturnValue(NanNew<String>(creator.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetKeywords) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString keywords = obj->_obj->GetKeywords();
  NanReturnValue(NanNew<String>(keywords.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetSubject) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString subject = obj->_obj->GetSubject();
  NanReturnValue(NanNew<String>(subject.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetTitle) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString title = obj->_obj->GetTitle();
  NanReturnValue(NanNew<String>(title.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetProducer) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfString producer = obj->_obj->GetProducer();
  NanReturnValue(NanNew<String>(producer.GetStringUtf8()));
}

NAN_METHOD(PdfInfo::GetTrapped) {
  NanScope();
  PdfInfo* obj = ObjectWrap::Unwrap<PdfInfo>(args.This());
  PoDoFo::PdfName trapped = obj->_obj->GetTrapped();
  NanReturnValue(NanNew<String>(trapped.GetName()));
}

