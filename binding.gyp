{
  "targets": [
    {
      "target_name": "podofo",
      "sources": [
        "PdfContentsTokenizer.cc",
        "PdfError.cc",
        "PdfInfo.cc",
        "PdfMemDocument.cc",
        "PdfObject.cc",
        "PdfParser.cc",
        "PdfPage.cc",
        "PdfVariant.cc",
        "PdfVecObjects.cc",
        "podofo.cc"
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
      "conditions": [
        ["OS=='win'", {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          },
          "link_settings": {
            "libraries": ["ws2_32.lib"]
          },
          "dependencies": [
            "deps/podofo.gypi:libpodofo"
          ]
        }, {
          "link_settings": {
            "libraries": ["-lpodofo"]
          }
        }],
        ["OS=='mac'", {
          "xcode_settings": {
           "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
       }]
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/usr/include/podofo",
        "/usr/local/include/podofo"
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}
