#ifndef NODE_PODOFO_PDF_OBJECT_H
#define NODE_PODOFO_PDF_OBJECT_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfObject : public node::ObjectWrap {
public:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);

  explicit PdfObject();
  explicit PdfObject(PoDoFo::PdfObject* obj);
  ~PdfObject();

  PoDoFo::PdfObject* _obj;
  bool _objFromElsewhere;
};

#endif
