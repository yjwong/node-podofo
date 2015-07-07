{
  "targets": [
    {
      "target_name": "podofo",
      "sources": [
        "PdfContentsTokenizer.cc",
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
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/usr/include/podofo"
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
