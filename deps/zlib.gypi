# Copyright 2014 Google Inc.
#
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  "targets": [
    {
      "target_name": "zlib",
      "type": "static_library",
      "cflags": [ "-w" ],
      "sources": [
        "zlib-1.2.8/adler32.c",
        "zlib-1.2.8/compress.c",
        "zlib-1.2.8/crc32.c",
        "zlib-1.2.8/deflate.c",
        "zlib-1.2.8/gzclose.c",
        "zlib-1.2.8/gzlib.c",
        "zlib-1.2.8/gzread.c",
        "zlib-1.2.8/gzwrite.c",
        "zlib-1.2.8/infback.c",
        "zlib-1.2.8/inffast.c",
        "zlib-1.2.8/inflate.c",
        "zlib-1.2.8/inftrees.c",
        "zlib-1.2.8/trees.c",
        "zlib-1.2.8/uncompr.c",
        "zlib-1.2.8/zutil.c",
      ],
      "include_dirs": [
        "zlib-1.2.8/",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "zlib-1.2.8/",
        ]
      }
    }
  ]
}