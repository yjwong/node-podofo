#ifndef NODE_PODOFO_PDF_INFO_H
#define NODE_PODOFO_PDF_INFO_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfInfo : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);
  static NAN_METHOD(GetAuthor);
  static NAN_METHOD(GetCreator);
  static NAN_METHOD(GetKeywords);
  static NAN_METHOD(GetSubject);
  static NAN_METHOD(GetTitle);
  static NAN_METHOD(GetProducer);
  static NAN_METHOD(GetTrapped);

  explicit PdfInfo(PoDoFo::PdfInfo* obj);
  ~PdfInfo();

  PoDoFo::PdfInfo* _obj;
};

#endif
