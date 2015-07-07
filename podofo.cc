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

  DefineConstant(exports, "ePdfDataType_Bool", PoDoFo::ePdfDataType_Bool);
  DefineConstant(exports, "ePdfDataType_Number", PoDoFo::ePdfDataType_Number);
  DefineConstant(exports, "ePdfDataType_Real", PoDoFo::ePdfDataType_Real);
  DefineConstant(exports, "ePdfDataType_String", PoDoFo::ePdfDataType_String);
  DefineConstant(exports, "ePdfDataType_HexString", PoDoFo::ePdfDataType_HexString);
  DefineConstant(exports, "ePdfDataType_Name", PoDoFo::ePdfDataType_Name);
  DefineConstant(exports, "ePdfDataType_Array", PoDoFo::ePdfDataType_Array);
  DefineConstant(exports, "ePdfDataType_Dictionary", PoDoFo::ePdfDataType_Dictionary);
  DefineConstant(exports, "ePdfDataType_Null", PoDoFo::ePdfDataType_Null);
  DefineConstant(exports, "ePdfDataType_Reference", PoDoFo::ePdfDataType_Reference);
  DefineConstant(exports, "ePdfDataType_RawData", PoDoFo::ePdfDataType_RawData);
  DefineConstant(exports, "ePdfDataType_Unknown", PoDoFo::ePdfDataType_Unknown);
}

NODE_MODULE(podofo, InitAll)
