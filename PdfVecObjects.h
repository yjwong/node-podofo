#ifndef NODE_PODOFO_PDF_VEC_OBJECTS_H
#define NODE_PODOFO_PDF_VEC_OBJECTS_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfVecObjects : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);
  PoDoFo::PdfVecObjects* Unwrap();

private:
  static NAN_METHOD(New);
  static NAN_METHOD(GetSize);
  static NAN_METHOD(GetObjectCount);
  static NAN_METHOD(ToArray);

  explicit PdfVecObjects();
  explicit PdfVecObjects(PoDoFo::PdfVecObjects* obj);
  ~PdfVecObjects();

  PoDoFo::PdfVecObjects* _obj;
  bool _objFromElsewhere;
};

#endif
