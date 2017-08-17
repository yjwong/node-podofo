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
        "podofo/src/base/PdfArray.cpp",
        "podofo/src/base/PdfCanvas.cpp",
        "podofo/src/base/PdfColor.cpp",
        "podofo/src/base/PdfContentsTokenizer.cpp",
        "podofo/src/base/PdfData.cpp",
        "podofo/src/base/PdfDataType.cpp",
        "podofo/src/base/PdfDate.cpp",
        "podofo/src/base/PdfDictionary.cpp",
        "podofo/src/base/PdfEncoding.cpp",
        "podofo/src/base/PdfEncodingFactory.cpp",
        "podofo/src/base/PdfEncrypt.cpp",
        "podofo/src/base/PdfError.cpp",
        "podofo/src/base/PdfFileStream.cpp",
        "podofo/src/base/PdfFilter.cpp",
        "podofo/src/base/PdfFiltersPrivate.cpp",
        "podofo/src/base/PdfImmediateWriter.cpp",
        "podofo/src/base/PdfInputDevice.cpp",
        "podofo/src/base/PdfInputStream.cpp",
        "podofo/src/base/PdfLocale.cpp",
        "podofo/src/base/PdfMemStream.cpp",
        "podofo/src/base/PdfMemoryManagement.cpp",
        "podofo/src/base/PdfName.cpp",
        "podofo/src/base/PdfObject.cpp",
        "podofo/src/base/PdfObjectStreamParserObject.cpp",
        "podofo/src/base/PdfOutputDevice.cpp",
        "podofo/src/base/PdfOutputStream.cpp",
        "podofo/src/base/PdfParser.cpp",
        "podofo/src/base/PdfParserObject.cpp",
        "podofo/src/base/PdfRect.cpp",
        "podofo/src/base/PdfRefCountedBuffer.cpp",
        "podofo/src/base/PdfRefCountedInputDevice.cpp",
        "podofo/src/base/PdfReference.cpp",
        "podofo/src/base/PdfStream.cpp",
        "podofo/src/base/PdfString.cpp",
        "podofo/src/base/PdfTokenizer.cpp",
        "podofo/src/base/PdfVariant.cpp",
        "podofo/src/base/PdfVecObjects.cpp",
        "podofo/src/base/PdfWriter.cpp",
        "podofo/src/base/PdfXRef.cpp",
        "podofo/src/base/PdfXRefStream.cpp",
        "podofo/src/base/PdfXRefStreamParserObject.cpp",

        # From PODOFO_DOC_SOURCES,
        "podofo/src/doc/PdfAcroForm.cpp",
        "podofo/src/doc/PdfAction.cpp",
        "podofo/src/doc/PdfAnnotation.cpp",
        "podofo/src/doc/PdfCMapEncoding.cpp",
        "podofo/src/doc/PdfContents.cpp",
        "podofo/src/doc/PdfDestination.cpp",
        "podofo/src/doc/PdfDifferenceEncoding.cpp",
        "podofo/src/doc/PdfDocument.cpp",
        "podofo/src/doc/PdfElement.cpp",
        "podofo/src/doc/PdfEncodingObjectFactory.cpp",
        "podofo/src/doc/PdfExtGState.cpp",
        "podofo/src/doc/PdfField.cpp",
        "podofo/src/doc/PdfFileSpec.cpp",
        "podofo/src/doc/PdfFont.cpp",
        "podofo/src/doc/PdfFontCID.cpp",
        "podofo/src/doc/PdfFontCache.cpp",
        "podofo/src/doc/PdfFontConfigWrapper.cpp",
        "podofo/src/doc/PdfFontFactory.cpp",
        "podofo/src/doc/PdfFontMetrics.cpp",
        "podofo/src/doc/PdfFontMetricsBase14.cpp",
        "podofo/src/doc/PdfFontMetricsFreetype.cpp",
        "podofo/src/doc/PdfFontMetricsObject.cpp",
        "podofo/src/doc/PdfFontSimple.cpp",
        "podofo/src/doc/PdfFontTTFSubset.cpp",
        "podofo/src/doc/PdfFontTrueType.cpp",
        "podofo/src/doc/PdfFontType1.cpp",
        "podofo/src/doc/PdfFontType1Base14.cpp",
        "podofo/src/doc/PdfFontType3.cpp",
        "podofo/src/doc/PdfFunction.cpp",
        "podofo/src/doc/PdfHintStream.cpp",
        "podofo/src/doc/PdfIdentityEncoding.cpp",
        "podofo/src/doc/PdfImage.cpp",
        "podofo/src/doc/PdfInfo.cpp",
        "podofo/src/doc/PdfMemDocument.cpp",
        "podofo/src/doc/PdfNamesTree.cpp",
        "podofo/src/doc/PdfOutlines.cpp",
        "podofo/src/doc/PdfPage.cpp",
        "podofo/src/doc/PdfPagesTree.cpp",
        "podofo/src/doc/PdfPagesTreeCache.cpp",
        "podofo/src/doc/PdfPainter.cpp",
        "podofo/src/doc/PdfPainterMM.cpp",
        "podofo/src/doc/PdfShadingPattern.cpp",
        "podofo/src/doc/PdfSignOutputDevice.cpp",
        "podofo/src/doc/PdfSignatureField.cpp",
        "podofo/src/doc/PdfStreamedDocument.cpp",
        "podofo/src/doc/PdfTable.cpp",
        "podofo/src/doc/PdfTilingPattern.cpp",
        "podofo/src/doc/PdfXObject.cpp",
      ],
      "conditions": [
        ["OS=='win'", {
          "cflags": [
            "/EHsc"
          ]
        }],
        ["OS=='linux'", {
          "cflags_cc!": [
            "-fno-exceptions",
            "-fno-rtti"
          ]
        }],
        ["OS=='mac'", {
          "xcode_settings": {
           "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
           "GCC_ENABLE_CPP_RTTI": "YES"
          }
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
        "podofo/podofo/",
        "podofo/src/",
        "podofo/",
        "overrides/<(OS)/<(target_arch)/"
      ],
      "dependencies": [
        "zlib.gypi:zlib",
        "freetype.gypi:libfreetype"
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "podofo/src/",
          "podofo/",
          "overrides/<(OS)/<(target_arch)/"
        ]
      }
    }
  ]
}
