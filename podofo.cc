#include <node.h>
#include "PdfContentsTokenizer.h"
#include "PdfError.h"
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
  exports->ForceSet(Nan::New<String>(name).ToLocalChecked(), Nan::New<Number>(value), attributes);
}

void InitAll(Handle<Object> exports) {

  PdfContentsTokenizer::Init(exports);
  PdfError::Init(exports);
  PdfInfo::Init(exports);
  PdfMemDocument::Init(exports);
  PdfPage::Init(exports);
  PdfParser::Init(exports);
  PdfVariant::Init(exports);
  PdfObject::Init(exports);
  PdfVecObjects::Init(exports);

  DefineConstant(exports, "eLogSeverity_None ", PoDoFo::eLogSeverity_None);

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

  DefineConstant(exports, "ePdfError_ErrOk", PoDoFo::ePdfError_ErrOk);
  DefineConstant(exports, "ePdfError_TestFailed", PoDoFo::ePdfError_TestFailed);
  DefineConstant(exports, "ePdfError_InvalidHandle", PoDoFo::ePdfError_InvalidHandle);
  DefineConstant(exports, "ePdfError_FileNotFound", PoDoFo::ePdfError_FileNotFound);
  DefineConstant(exports, "ePdfError_InvalidDeviceOperation", PoDoFo::ePdfError_InvalidDeviceOperation);
  DefineConstant(exports, "ePdfError_UnexpectedEOF", PoDoFo::ePdfError_UnexpectedEOF);
  DefineConstant(exports, "ePdfError_OutOfMemory", PoDoFo::ePdfError_OutOfMemory);
  DefineConstant(exports, "ePdfError_ValueOutOfRange", PoDoFo::ePdfError_ValueOutOfRange);
  DefineConstant(exports, "ePdfError_InternalLogic", PoDoFo::ePdfError_InternalLogic);
  DefineConstant(exports, "ePdfError_InvalidEnumValue", PoDoFo::ePdfError_InvalidEnumValue);
  DefineConstant(exports, "ePdfError_PageNotFound", PoDoFo::ePdfError_PageNotFound);
  DefineConstant(exports, "ePdfError_NoPdfFile", PoDoFo::ePdfError_NoPdfFile);
  DefineConstant(exports, "ePdfError_NoXRef", PoDoFo::ePdfError_NoXRef);
  DefineConstant(exports, "ePdfError_NoTrailer", PoDoFo::ePdfError_NoTrailer);
  DefineConstant(exports, "ePdfError_NoNumber", PoDoFo::ePdfError_NoNumber);
  DefineConstant(exports, "ePdfError_NoObject", PoDoFo::ePdfError_NoObject);
  DefineConstant(exports, "ePdfError_NoEOFToken", PoDoFo::ePdfError_NoEOFToken);
  DefineConstant(exports, "ePdfError_InvalidTrailerSize", PoDoFo::ePdfError_InvalidTrailerSize);
  DefineConstant(exports, "ePdfError_InvalidLinearization", PoDoFo::ePdfError_InvalidLinearization);
  DefineConstant(exports, "ePdfError_InvalidDataType", PoDoFo::ePdfError_InvalidDataType);
  DefineConstant(exports, "ePdfError_InvalidXRef", PoDoFo::ePdfError_InvalidXRef);
  DefineConstant(exports, "ePdfError_InvalidXRefStream", PoDoFo::ePdfError_InvalidXRefStream);
  DefineConstant(exports, "ePdfError_InvalidXRefType", PoDoFo::ePdfError_InvalidXRefType);
  DefineConstant(exports, "ePdfError_InvalidPredictor", PoDoFo::ePdfError_InvalidPredictor);
  DefineConstant(exports, "ePdfError_InvalidStrokeStyle", PoDoFo::ePdfError_InvalidStrokeStyle);
  DefineConstant(exports, "ePdfError_InvalidHexString", PoDoFo::ePdfError_InvalidHexString);
  DefineConstant(exports, "ePdfError_InvalidStream", PoDoFo::ePdfError_InvalidStream);
  DefineConstant(exports, "ePdfError_InvalidStreamLength", PoDoFo::ePdfError_InvalidStreamLength);
  DefineConstant(exports, "ePdfError_InvalidKey", PoDoFo::ePdfError_InvalidKey);
  DefineConstant(exports, "ePdfError_InvalidName", PoDoFo::ePdfError_InvalidName);
  DefineConstant(exports, "ePdfError_InvalidEncryptionDict", PoDoFo::ePdfError_InvalidEncryptionDict);
  DefineConstant(exports, "ePdfError_InvalidPassword", PoDoFo::ePdfError_InvalidPassword);
  DefineConstant(exports, "ePdfError_InvalidFontFile", PoDoFo::ePdfError_InvalidFontFile);
  DefineConstant(exports, "ePdfError_InvalidContentStream", PoDoFo::ePdfError_InvalidContentStream);
  DefineConstant(exports, "ePdfError_UnsupportedFilter", PoDoFo::ePdfError_UnsupportedFilter);
  DefineConstant(exports, "ePdfError_UnsupportedFontFormat", PoDoFo::ePdfError_UnsupportedFontFormat);
  DefineConstant(exports, "ePdfError_ActionAlreadyPresent", PoDoFo::ePdfError_ActionAlreadyPresent);
  DefineConstant(exports, "ePdfError_WrongDestinationType", PoDoFo::ePdfError_WrongDestinationType);
  DefineConstant(exports, "ePdfError_MissingEndStream", PoDoFo::ePdfError_MissingEndStream);
  DefineConstant(exports, "ePdfError_Date", PoDoFo::ePdfError_Date);
  DefineConstant(exports, "ePdfError_Flate", PoDoFo::ePdfError_Flate);
  DefineConstant(exports, "ePdfError_FreeType", PoDoFo::ePdfError_FreeType);
  DefineConstant(exports, "ePdfError_SignatureError", PoDoFo::ePdfError_SignatureError);
  DefineConstant(exports, "ePdfError_MutexError", PoDoFo::ePdfError_MutexError);
  DefineConstant(exports, "ePdfError_UnsupportedImageFormat", PoDoFo::ePdfError_UnsupportedImageFormat);
  DefineConstant(exports, "ePdfError_CannotConvertColor", PoDoFo::ePdfError_CannotConvertColor);
  DefineConstant(exports, "ePdfError_NotImplemented", PoDoFo::ePdfError_NotImplemented);
  DefineConstant(exports, "ePdfError_DestinationAlreadyPresent", PoDoFo::ePdfError_DestinationAlreadyPresent);
  DefineConstant(exports, "ePdfError_ChangeOnImmutable", PoDoFo::ePdfError_ChangeOnImmutable);
  DefineConstant(exports, "ePdfError_Unknown", PoDoFo::ePdfError_Unknown);
}

NODE_MODULE(podofo, InitAll)
