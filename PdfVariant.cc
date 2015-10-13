#include <node.h>
#include "PdfObject.h"
#include "PdfVariant.h"

using v8::Handle;
using v8::Value;
using v8::Object;
using v8::Local;
using v8::FunctionTemplate;
using v8::Function;
using v8::Number;
using v8::String;
using v8::Array;
using v8::External;

Nan::Persistent<FunctionTemplate> PdfVariant::constructor_template;

PdfVariant::PdfVariant() :
  _obj(new PoDoFo::PdfVariant()),
  _objFromElsewhere(false) { }

PdfVariant::PdfVariant(PoDoFo::PdfVariant* obj) :
  _obj(obj),
  _objFromElsewhere(true) { }

PdfVariant::~PdfVariant() {
	delete _obj;
}

void PdfVariant::Init(Handle<Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("PdfVariant").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(30);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "IsEmpty", IsEmpty);
  Nan::SetPrototypeMethod(tpl, "Clear", Clear);
  Nan::SetPrototypeMethod(tpl, "GetDataType", GetDataType);
  Nan::SetPrototypeMethod(tpl, "GetDataTypeString", GetDataTypeString);
  Nan::SetPrototypeMethod(tpl, "IsBool", IsBool);
  Nan::SetPrototypeMethod(tpl, "IsNumber", IsNumber);
  Nan::SetPrototypeMethod(tpl, "IsReal", IsReal);
  Nan::SetPrototypeMethod(tpl, "IsString", IsString);
  Nan::SetPrototypeMethod(tpl, "IsHexString", IsHexString);
  Nan::SetPrototypeMethod(tpl, "IsName", IsName);
  Nan::SetPrototypeMethod(tpl, "IsArray", IsArray);
  Nan::SetPrototypeMethod(tpl, "IsDictionary", IsDictionary);
  Nan::SetPrototypeMethod(tpl, "IsRawData", IsRawData);
  Nan::SetPrototypeMethod(tpl, "IsNull", IsNull);
  Nan::SetPrototypeMethod(tpl, "IsReference", IsReference);
  Nan::SetPrototypeMethod(tpl, "SetBool", SetBool);
  Nan::SetPrototypeMethod(tpl, "GetBool", GetBool);
  Nan::SetPrototypeMethod(tpl, "SetNumber", SetNumber);
  Nan::SetPrototypeMethod(tpl, "GetNumber", GetNumber);
  Nan::SetPrototypeMethod(tpl, "SetReal", SetReal);
  Nan::SetPrototypeMethod(tpl, "GetReal", GetReal);
  Nan::SetPrototypeMethod(tpl, "GetString", GetString);
  Nan::SetPrototypeMethod(tpl, "GetName", GetName);
  Nan::SetPrototypeMethod(tpl, "GetArray", GetArray);
  Nan::SetPrototypeMethod(tpl, "GetDictionary", GetDictionary);
  Nan::SetPrototypeMethod(tpl, "GetRawData", GetRawData);
  Nan::SetPrototypeMethod(tpl, "IsDirty", IsDirty);
  Nan::SetPrototypeMethod(tpl, "SetImmutable", SetImmutable);
  Nan::SetPrototypeMethod(tpl, "GetImmutable", GetImmutable);

  constructor_template.Reset(tpl); 
  exports->Set(Nan::New("PdfVariant").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(PdfVariant::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError("Use the new operator to create new PdfVariant objects");
  }

  PdfVariant* objects;
  if (info.Length() == 1 && info[0]->IsExternal()) {
    objects = new PdfVariant(static_cast<PoDoFo::PdfVariant*>(
          External::Cast(*info[0])->Value()));
  } else {
    objects = new PdfVariant();
  }

  objects->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(PdfVariant::IsEmpty) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsEmpty() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::Clear) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  obj->_obj->Clear();
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::GetDataType) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(obj->_obj->GetDataType()));
}

NAN_METHOD(PdfVariant::GetDataTypeString) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());

  // PoDoFo documentation says that the char* returned by GetDataTypeString
  // should not be free'd.
  std::string str = std::string(obj->_obj->GetDataTypeString());
  info.GetReturnValue().Set(Nan::New<String>(str.c_str()).ToLocalChecked());
}

NAN_METHOD(PdfVariant::IsBool) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsBool() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsNumber) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsNumber() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsReal) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsReal() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsString) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsString() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsHexString) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsHexString() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsName) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsName() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsArray) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsArray() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsDictionary) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsDictionary() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsRawData) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsRawData() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsNull) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsNull() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::IsReference) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsReference() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::SetBool) {
  Nan::HandleScope scope;

  if (info.Length() != 1) {
    return Nan::ThrowTypeError("SetBool requires exactly 1 argument");
  }

  if (!info[0]->IsBoolean()) {
    return Nan::ThrowTypeError("SetBool requires a boolean argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  obj->_obj->SetBool(info[0]->ToBoolean()->Value());

  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::GetBool) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->GetBool() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::SetNumber) {
  Nan::HandleScope scope;

  if (info.Length() != 1) {
    return Nan::ThrowTypeError("SetNumber requires exactly 1 argument");
  }

  if (!info[0]->IsNumber()) {
    return Nan::ThrowTypeError("SetNumber requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  obj->_obj->SetNumber(info[0]->NumberValue());

  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::GetNumber) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(obj->_obj->GetNumber()));
}

NAN_METHOD(PdfVariant::SetReal) {
  Nan::HandleScope scope;

  if (info.Length() != 1) {
    return Nan::ThrowTypeError("SetReal requires exactly 1 argument");
  }

  if (!info[0]->IsNumber()) {
    return Nan::ThrowTypeError("SetReal requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  obj->_obj->SetReal(info[0]->NumberValue());

  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::GetReal) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(obj->_obj->GetReal()));
}

NAN_METHOD(PdfVariant::GetString) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(Nan::New<String>(obj->_obj->GetString().GetStringUtf8()).ToLocalChecked());
}

NAN_METHOD(PdfVariant::GetName) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(Nan::New<String>(obj->_obj->GetName().GetName()).ToLocalChecked());
}

NAN_METHOD(PdfVariant::GetArray) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  
  PoDoFo::PdfArray arr = obj->_obj->GetArray();
  Local<Array> newArr = Nan::New<Array>(arr.size());

  // Iterate through the native PdfArray, which is essentially a std::vector.
  // Each item is a native PdfObject which we must wrap.
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  for (PoDoFo::PdfArray::iterator it = arr.begin(); it != arr.end(); ++it) {
    PoDoFo::PdfObject* obj = new PoDoFo::PdfObject(*it);

    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { Nan::New<External>(obj) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);

    newArr->Set(std::distance(arr.begin(), it), newObj);
  }

  info.GetReturnValue().Set(newArr);
}

NAN_METHOD(PdfVariant::GetDictionary) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());

  PoDoFo::PdfDictionary dict = obj->_obj->GetDictionary();
  Local<Object> returnObj = Nan::New<Object>();

  // Iterate through the native PdfDictionary, which is essentially an std::map
  // between a PdfName and PdfObject*.
  Local<FunctionTemplate> tpl = Nan::New(PdfObject::constructor_template);
  PoDoFo::TKeyMap keys = dict.GetKeys();
  for (PoDoFo::TKeyMap::iterator it = keys.begin(); it != keys.end(); ++it) {
    PoDoFo::PdfName key = it->first;
    PoDoFo::PdfObject* val = new PoDoFo::PdfObject(*it->second);

    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { Nan::New<External>(val) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);

    returnObj->Set(Nan::New<String>(key.GetName()).ToLocalChecked(), newObj);
  }

  info.GetReturnValue().Set(returnObj);
}

// TODO: This is a stub implemenentation because it requires PdfReference to
// be implemented first.
NAN_METHOD(PdfVariant::GetReference) {
  Nan::HandleScope scope;
  info.GetReturnValue().Set(Nan::Undefined());
}

// TODO: This is a stub implemenentation because it requires PdfData to be
// implemented first.
NAN_METHOD(PdfVariant::GetRawData) {
  Nan::HandleScope scope;
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::IsDirty) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->IsDirty() ? Nan::True() : Nan::False());
}

NAN_METHOD(PdfVariant::SetImmutable) {
  Nan::HandleScope scope;

  if (info.Length() != 1) {
    return Nan::ThrowTypeError("SetImmutable requires exactly 1 argument");
  }

  if (!info[0]->IsBoolean()) {
    return Nan::ThrowTypeError("SetImmutable requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  obj->_obj->SetImmutable(info[0]->ToBoolean()->Value());

  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PdfVariant::GetImmutable) {
  Nan::HandleScope scope;
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(info.This());
  info.GetReturnValue().Set(obj->_obj->GetImmutable() ? Nan::True() : Nan::False());
}

