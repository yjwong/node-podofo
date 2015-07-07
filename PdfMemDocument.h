#ifndef NODE_PODOFO_PDF_MEM_DOCUMENT_H
#define NODE_PODOFO_PDF_MEM_DOCUMENT_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfMemDocument : public node::ObjectWrap {
public:
  static void Init(v8::Handle<v8::Object> exports);

private:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  static NAN_METHOD(New);
  static NAN_METHOD(Load);
  static NAN_METHOD(GetObjects);

  // Inherited from PdfDocument
  static NAN_METHOD(GetInfo);
  static NAN_METHOD(GetPageCount);
  static NAN_METHOD(GetPage);

  explicit PdfMemDocument();
  ~PdfMemDocument();

  PoDoFo::PdfMemDocument* _obj;
};

#endif
