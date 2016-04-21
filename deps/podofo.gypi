# Copyright 2014 Google Inc.
#
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  "targets": [
    {
      "target_name": "libpodofo",
      "type": "static_library",
      "cflags": [ "-w" ],
      "defines": [
        "BUILDING_PODOFO=1"
      ],
      "sources": [
        # From PODOFO_BASE_SOURCES
        "podofo-0.9.3/src/base/PdfArray.cpp",
        "podofo-0.9.3/src/base/PdfCanvas.cpp",
        "podofo-0.9.3/src/base/PdfColor.cpp",
        "podofo-0.9.3/src/base/PdfContentsTokenizer.cpp",
        "podofo-0.9.3/src/base/PdfData.cpp",
        "podofo-0.9.3/src/base/PdfDataType.cpp",
        "podofo-0.9.3/src/base/PdfDate.cpp",
        "podofo-0.9.3/src/base/PdfDictionary.cpp",
        "podofo-0.9.3/src/base/PdfEncoding.cpp",
        "podofo-0.9.3/src/base/PdfEncodingFactory.cpp",
        "podofo-0.9.3/src/base/PdfEncrypt.cpp",
        "podofo-0.9.3/src/base/PdfError.cpp",
        "podofo-0.9.3/src/base/PdfFileStream.cpp",
        "podofo-0.9.3/src/base/PdfFilter.cpp",
        "podofo-0.9.3/src/base/PdfFiltersPrivate.cpp",
        "podofo-0.9.3/src/base/PdfImmediateWriter.cpp",
        "podofo-0.9.3/src/base/PdfInputDevice.cpp",
        "podofo-0.9.3/src/base/PdfInputStream.cpp",
        "podofo-0.9.3/src/base/PdfLocale.cpp",
        "podofo-0.9.3/src/base/PdfMemStream.cpp",
        "podofo-0.9.3/src/base/PdfMemoryManagement.cpp",
        "podofo-0.9.3/src/base/PdfName.cpp",
        "podofo-0.9.3/src/base/PdfObject.cpp",
        "podofo-0.9.3/src/base/PdfObjectStreamParserObject.cpp",
        "podofo-0.9.3/src/base/PdfOutputDevice.cpp",
        "podofo-0.9.3/src/base/PdfOutputStream.cpp",
        "podofo-0.9.3/src/base/PdfParser.cpp",
        "podofo-0.9.3/src/base/PdfParserObject.cpp",
        "podofo-0.9.3/src/base/PdfRect.cpp",
        "podofo-0.9.3/src/base/PdfRefCountedBuffer.cpp",
        "podofo-0.9.3/src/base/PdfRefCountedInputDevice.cpp",
        "podofo-0.9.3/src/base/PdfReference.cpp",
        "podofo-0.9.3/src/base/PdfSigIncWriter.cpp",
        "podofo-0.9.3/src/base/PdfStream.cpp",
        "podofo-0.9.3/src/base/PdfString.cpp",
        "podofo-0.9.3/src/base/PdfTokenizer.cpp",
        "podofo-0.9.3/src/base/PdfVariant.cpp",
        "podofo-0.9.3/src/base/PdfVecObjects.cpp",
        "podofo-0.9.3/src/base/PdfWriter.cpp",
        "podofo-0.9.3/src/base/PdfXRef.cpp",
        "podofo-0.9.3/src/base/PdfXRefStream.cpp",
        "podofo-0.9.3/src/base/PdfXRefStreamParserObject.cpp",

        # From PODOFO_DOC_SOURCES
        "podofo-0.9.3/src/doc/PdfAcroForm.cpp",
        "podofo-0.9.3/src/doc/PdfAction.cpp",
        "podofo-0.9.3/src/doc/PdfAnnotation.cpp",
        "podofo-0.9.3/src/doc/PdfCMapEncoding.cpp",
        "podofo-0.9.3/src/doc/PdfContents.cpp",
        "podofo-0.9.3/src/doc/PdfDestination.cpp",
        "podofo-0.9.3/src/doc/PdfDifferenceEncoding.cpp",
        "podofo-0.9.3/src/doc/PdfDocument.cpp",
        "podofo-0.9.3/src/doc/PdfElement.cpp",
        "podofo-0.9.3/src/doc/PdfEncodingObjectFactory.cpp",
        "podofo-0.9.3/src/doc/PdfExtGState.cpp",
        "podofo-0.9.3/src/doc/PdfField.cpp",
        "podofo-0.9.3/src/doc/PdfFileSpec.cpp",
        "podofo-0.9.3/src/doc/PdfFont.cpp",
        "podofo-0.9.3/src/doc/PdfFontCID.cpp",
        "podofo-0.9.3/src/doc/PdfFontCache.cpp",
        "podofo-0.9.3/src/doc/PdfFontConfigWrapper.cpp",
        "podofo-0.9.3/src/doc/PdfFontFactory.cpp",
        "podofo-0.9.3/src/doc/PdfFontMetrics.cpp",
        "podofo-0.9.3/src/doc/PdfFontMetricsBase14.cpp",
        "podofo-0.9.3/src/doc/PdfFontMetricsFreetype.cpp",
        "podofo-0.9.3/src/doc/PdfFontMetricsObject.cpp",
        "podofo-0.9.3/src/doc/PdfFontSimple.cpp",
        "podofo-0.9.3/src/doc/PdfFontTTFSubset.cpp",
        "podofo-0.9.3/src/doc/PdfFontTrueType.cpp",
        "podofo-0.9.3/src/doc/PdfFontType1.cpp",
        "podofo-0.9.3/src/doc/PdfFontType3.cpp",
        "podofo-0.9.3/src/doc/PdfFontType1Base14.cpp",
        "podofo-0.9.3/src/doc/PdfFunction.cpp",
        "podofo-0.9.3/src/doc/PdfHintStream.cpp",
        "podofo-0.9.3/src/doc/PdfIdentityEncoding.cpp",
        "podofo-0.9.3/src/doc/PdfImage.cpp",
        "podofo-0.9.3/src/doc/PdfInfo.cpp",
        "podofo-0.9.3/src/doc/PdfMemDocument.cpp",
        "podofo-0.9.3/src/doc/PdfNamesTree.cpp",
        "podofo-0.9.3/src/doc/PdfOutlines.cpp",
        "podofo-0.9.3/src/doc/PdfPage.cpp",
        "podofo-0.9.3/src/doc/PdfPagesTree.cpp",
        "podofo-0.9.3/src/doc/PdfPagesTreeCache.cpp",
        "podofo-0.9.3/src/doc/PdfPainter.cpp",
        "podofo-0.9.3/src/doc/PdfPainterMM.cpp",
        "podofo-0.9.3/src/doc/PdfShadingPattern.cpp",
        "podofo-0.9.3/src/doc/PdfSigIncMemDocument.cpp",
        "podofo-0.9.3/src/doc/PdfSigIncPainter.cpp",
        "podofo-0.9.3/src/doc/PdfSigIncSignatureField.cpp",
        "podofo-0.9.3/src/doc/PdfSignOutputDevice.cpp",
        "podofo-0.9.3/src/doc/PdfSignatureField.cpp",
        "podofo-0.9.3/src/doc/PdfStreamedDocument.cpp",
        "podofo-0.9.3/src/doc/PdfTable.cpp",
        "podofo-0.9.3/src/doc/PdfTilingPattern.cpp",
        "podofo-0.9.3/src/doc/PdfXObject.cpp"
      ],
      "conditions": [
        ["OS=='win'", {
          "cflags": [
            "/EHsc"
          ]
       }]
      ],
      "configurations": {
        "Release": {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "RuntimeTypeInfo": "true"
            }
          }
        }
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      },
      "include_dirs": [
        "podofo-0.9.3/podofo/",
        "podofo-0.9.3/src/",
        "podofo-0.9.3/",
        "./"
      ],
      "dependencies": [
        "zlib.gypi:zlib",
        "freetype.gypi:libfreetype"
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "podofo-0.9.3/src/",
          "podofo-0.9.3/",
          "./"
        ]
      }
    }
  ]
}