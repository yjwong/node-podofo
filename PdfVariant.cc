#include <node.h>
#include "PdfObject.h"
#include "PdfVariant.h"

using v8::Handle;
using v8::Value;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::FunctionTemplate;
using v8::Function;
using v8::Number;
using v8::String;
using v8::Array;
using v8::External;

Persistent<FunctionTemplate> PdfVariant::constructor_template;

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
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("PdfVariant"));
  tpl->InstanceTemplate()->SetInternalFieldCount(30);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsEmpty", IsEmpty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Clear", Clear);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDataType", GetDataType);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDataTypeString", GetDataTypeString);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsBool", IsBool);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsNumber", IsNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsReal", IsReal);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsString", IsString);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsHexString", IsHexString);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsName", IsName);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsArray", IsArray);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsDictionary", IsDictionary);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsRawData", IsRawData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsNull", IsNull);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsReference", IsReference);
  NODE_SET_PROTOTYPE_METHOD(tpl, "SetBool", SetBool);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetBool", GetBool);
  NODE_SET_PROTOTYPE_METHOD(tpl, "SetNumber", SetNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetNumber", GetNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "SetReal", SetReal);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetReal", GetReal);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetString", GetString);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetName", GetName);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetArray", GetArray);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetDictionary", GetDictionary);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetRawData", GetRawData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "IsDirty", IsDirty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "SetImmutable", SetImmutable);
  NODE_SET_PROTOTYPE_METHOD(tpl, "GetImmutable", GetImmutable);
 
  NanAssignPersistent(constructor_template, tpl);
  exports->Set(NanNew("PdfVariant"), tpl->GetFunction());
}

NAN_METHOD(PdfVariant::New) {
  NanScope();

  if (!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to create new PdfVariant objects");
  }

  PdfVariant* objects;
  if (args.Length() == 1 && args[0]->IsExternal()) {
    objects = new PdfVariant(static_cast<PoDoFo::PdfVariant*>(
          External::Cast(*args[0])->Value()));
  } else {
    objects = new PdfVariant();
  }

  objects->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(PdfVariant::IsEmpty) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsEmpty() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::Clear) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  obj->_obj->Clear();
  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::GetDataType) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(NanNew<Number>(obj->_obj->GetDataType()));
}

NAN_METHOD(PdfVariant::GetDataTypeString) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());

  // PoDoFo documentation says that the char* returned by GetDataTypeString
  // should not be free'd.
  std::string str = std::string(obj->_obj->GetDataTypeString());
  NanReturnValue(NanNew<String>(str.c_str()));
}

NAN_METHOD(PdfVariant::IsBool) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsBool() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsNumber) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsNumber() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsReal) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsReal() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsString) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsString() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsHexString) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsHexString() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsName) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsName() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsArray) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsArray() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsDictionary) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsDictionary() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsRawData) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsRawData() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsNull) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsNull() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::IsReference) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsReference() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::SetBool) {
  NanScope();

  if (args.Length() != 1) {
    return NanThrowTypeError("SetBool requires exactly 1 argument");
  }

  if (!args[0]->IsBoolean()) {
    return NanThrowTypeError("SetBool requires a boolean argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  obj->_obj->SetBool(args[0]->ToBoolean()->Value());

  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::GetBool) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->GetBool() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::SetNumber) {
  NanScope();

  if (args.Length() != 1) {
    return NanThrowTypeError("SetNumber requires exactly 1 argument");
  }

  if (!args[0]->IsNumber()) {
    return NanThrowTypeError("SetNumber requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  obj->_obj->SetNumber(args[0]->NumberValue());

  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::GetNumber) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(NanNew<Number>(obj->_obj->GetNumber()));
}

NAN_METHOD(PdfVariant::SetReal) {
  NanScope();

  if (args.Length() != 1) {
    return NanThrowTypeError("SetReal requires exactly 1 argument");
  }

  if (!args[0]->IsNumber()) {
    return NanThrowTypeError("SetReal requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  obj->_obj->SetReal(args[0]->NumberValue());

  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::GetReal) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(NanNew<Number>(obj->_obj->GetReal()));
}

NAN_METHOD(PdfVariant::GetString) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(NanNew<String>(obj->_obj->GetString().GetStringUtf8()));
}

NAN_METHOD(PdfVariant::GetName) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(NanNew<String>(obj->_obj->GetName().GetName()));
}

NAN_METHOD(PdfVariant::GetArray) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  
  PoDoFo::PdfArray arr = obj->_obj->GetArray();
  Local<Array> newArr = NanNew<Array>(arr.size());

  // Iterate through the native PdfArray, which is essentially a std::vector.
  // Each item is a native PdfObject which we must wrap.
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  for (PoDoFo::PdfArray::iterator it = arr.begin(); it != arr.end(); ++it) {
    PoDoFo::PdfObject* obj = new PoDoFo::PdfObject(*it);

    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { NanNew<External>(obj) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);

    newArr->Set(std::distance(arr.begin(), it), newObj);
  }

  NanReturnValue(newArr);
}

NAN_METHOD(PdfVariant::GetDictionary) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());

  PoDoFo::PdfDictionary dict = obj->_obj->GetDictionary();
  Local<Object> returnObj = NanNew<Object>();

  // Iterate through the native PdfDictionary, which is essentially an std::map
  // between a PdfName and PdfObject*.
  Local<FunctionTemplate> tpl = NanNew(PdfObject::constructor_template);
  PoDoFo::TKeyMap keys = dict.GetKeys();
  for (PoDoFo::TKeyMap::iterator it = keys.begin(); it != keys.end(); ++it) {
    PoDoFo::PdfName key = it->first;
    PoDoFo::PdfObject* val = new PoDoFo::PdfObject(*it->second);

    Local<Function> func = tpl->GetFunction();
    Handle<Value> newFuncArgs[] = { NanNew<External>(val) };
    Local<Object> newObj = func->NewInstance(1, newFuncArgs);

    returnObj->Set(NanNew<String>(key.GetName()), newObj);
  }

  NanReturnValue(returnObj);
}

// TODO: This is a stub implemenentation because it requires PdfReference to
// be implemented first.
NAN_METHOD(PdfVariant::GetReference) {
  NanScope();
  NanReturnUndefined();
}

// TODO: This is a stub implemenentation because it requires PdfData to be
// implemented first.
NAN_METHOD(PdfVariant::GetRawData) {
  NanScope();
  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::IsDirty) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->IsDirty() ? NanTrue() : NanFalse());
}

NAN_METHOD(PdfVariant::SetImmutable) {
  NanScope();

  if (args.Length() != 1) {
    return NanThrowTypeError("SetImmutable requires exactly 1 argument");
  }

  if (!args[0]->IsBoolean()) {
    return NanThrowTypeError("SetImmutable requires a number argument");
  }

  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  obj->_obj->SetImmutable(args[0]->ToBoolean()->Value());

  NanReturnUndefined();
}

NAN_METHOD(PdfVariant::GetImmutable) {
  NanScope();
  PdfVariant* obj = ObjectWrap::Unwrap<PdfVariant>(args.This());
  NanReturnValue(obj->_obj->GetImmutable() ? NanTrue() : NanFalse());
}

