#include <node.h>
#include "PdfContentsTokenizer.h"
#include "PdfInfo.h"
#include "PdfMemDocument.h"
#include "PdfObject.h"
#include "PdfPage.h"
#include "PdfParser.h"
#include "PdfVariant.h"
#include "PdfVecObjects.h"

using namespace v8;

void DefineConstant(Handle<Object> exports, const char* name, int value) {
  PropertyAttribute attributes = static_cast<PropertyAttribute>(ReadOnly | DontDelete);
  exports->ForceSet(NanNew<String>(name), NanNew<Number>(value), attributes);
}

void InitAll(Handle<Object> exports) {
  PdfContentsTokenizer::Init(exports);
  PdfInfo::Init(exports);
  PdfMemDocument::Init(exports);
  PdfPage::Init(exports);
  PdfParser::Init(exports);
  PdfVariant::Init(exports);
  PdfObject::Init(exports);
  PdfVecObjects::Init(exports);

  DefineConstant(exports, "ePdfContentsType_Keyword", PoDoFo::ePdfContentsType_Keyword);
  DefineConstant(exports, "ePdfContentsType_Variant", PoDoFo::ePdfContentsType_Variant);
  DefineConstant(exports, "ePdfContentsType_ImageData", PoDoFo::ePdfContentsType_ImageData);
}

NODE_MODULE(podofo, InitAll)
