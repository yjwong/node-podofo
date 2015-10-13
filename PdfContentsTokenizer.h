#ifndef NODE_PODOFO_PDF_CONTENTS_TOKENIZER_H
#define NODE_PODOFO_PDF_CONTENTS_TOKENIZER_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

class PdfContentsTokenizer : public node::ObjectWrap {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);
  static NAN_METHOD(ReadNext);

  explicit PdfContentsTokenizer(PoDoFo::PdfCanvas* pCanvas);
  ~PdfContentsTokenizer();

  PoDoFo::PdfContentsTokenizer* _obj;
};

#endif
