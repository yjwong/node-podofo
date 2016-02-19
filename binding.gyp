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
        ['OS=="mac"', {
         'xcode_settings': {
           'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
         }
       }]
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/usr/include/podofo",
        "/usr/local/include/podofo"
      ],
      "link_settings": {
        "libraries": [
          "-lpodofo"
        ]
      }
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
