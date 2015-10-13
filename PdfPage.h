#ifndef NODE_PODOFO_PDF_PAGE_H
#define NODE_PODOFO_PDF_PAGE_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfPage : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);
  PoDoFo::PdfPage* Unwrap();

private:
  static NAN_METHOD(New);
  static NAN_METHOD(GetPageNumber);

  // Inherited from PdfCanvas
  static NAN_METHOD(GetContents);
  static NAN_METHOD(GetResources);
  
  // Inherited from PdfElement
  static NAN_METHOD(GetObject);

  explicit PdfPage(PoDoFo::PdfPage* obj);
  ~PdfPage();

  PoDoFo::PdfPage* _obj;
  bool _objFromElsewhere;
};

#endif
