#ifndef NODE_PODOFO_PDF_ERROR_H
#define NODE_PODOFO_PDF_ERROR_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfError : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);
  static NAN_METHOD(GetError);
  static NAN_METHOD(IsError);
  static NAN_METHOD(what);

  explicit PdfError(PoDoFo::PdfError* obj);
  ~PdfError();

  PoDoFo::PdfError* _obj;
};

#endif

