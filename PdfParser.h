#ifndef NODE_PODOFO_PDF_PARSER_H
#define NODE_PODOFO_PDF_PARSER_H

#include <node.h>
#include <node_object_wrap.h>
#include "nan.h"
#include "podofo.h"

#include "PdfVecObjects.h"

class PdfParser : public node::ObjectWrap {
public:
  static void Init(v8::Handle<v8::Object> exports);

private:
  static NAN_METHOD(New);
  static NAN_METHOD(ParseFile);
  static NAN_METHOD(QuickEncryptedCheck);
  static NAN_METHOD(GetNumberOfIncrementalUpdates);
  static NAN_METHOD(GetPdfVersionString);
  static Nan::Persistent<v8::FunctionTemplate> constructor_template;

  explicit PdfParser(PdfVecObjects* pVecObjects);
  ~PdfParser();

  PoDoFo::PdfParser* _obj;
  Nan::Utf8String* _filename;
};

#endif
