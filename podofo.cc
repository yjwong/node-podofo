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

void InitAll(Handle<Object> exports) {
  PdfContentsTokenizer::Init(exports);
  PdfInfo::Init(exports);
  PdfMemDocument::Init(exports);
  PdfPage::Init(exports);
  PdfParser::Init(exports);
  PdfVariant::Init(exports);
  PdfObject::Init(exports);
  PdfVecObjects::Init(exports);
}

NODE_MODULE(podofo, InitAll)
