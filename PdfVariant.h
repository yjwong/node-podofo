#ifndef NODE_PODOFO_PDF_VARIANT_H
#define NODE_PODOFO_PDF_VARIANT_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfVariant : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);
  static NAN_METHOD(IsEmpty);
  static NAN_METHOD(Clear);
  static NAN_METHOD(GetDataType);
  static NAN_METHOD(GetDataTypeString);
  static NAN_METHOD(IsBool);
  static NAN_METHOD(IsNumber);
  static NAN_METHOD(IsReal);
  static NAN_METHOD(IsString);
  static NAN_METHOD(IsHexString);
  static NAN_METHOD(IsName);
  static NAN_METHOD(IsArray);
  static NAN_METHOD(IsDictionary);
  static NAN_METHOD(IsRawData);
  static NAN_METHOD(IsNull);
  static NAN_METHOD(IsReference);
  static NAN_METHOD(SetBool);
  static NAN_METHOD(GetBool);
  static NAN_METHOD(SetNumber);
  static NAN_METHOD(GetNumber);
  static NAN_METHOD(SetReal);
  static NAN_METHOD(GetReal);
  static NAN_METHOD(GetString);
  static NAN_METHOD(GetName);
  static NAN_METHOD(GetArray);
  static NAN_METHOD(GetDictionary);
  static NAN_METHOD(GetReference);
  static NAN_METHOD(GetRawData);
  static NAN_METHOD(IsDirty);
  static NAN_METHOD(SetImmutable);
  static NAN_METHOD(GetImmutable);

  explicit PdfVariant();
  explicit PdfVariant(PoDoFo::PdfVariant* obj);
  ~PdfVariant();

  PoDoFo::PdfVariant* _obj;
  bool _objFromElsewhere;
};

#endif
