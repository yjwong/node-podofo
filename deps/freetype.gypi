{
  "targets": [
    {
      "target_name": "libfreetype",
      "type": "static_library",
      "defines": [
        "FT2_BUILD_LIBRARY",
      ],
      "include_dirs": [
        "freetype-2.6.3/include/",
      ],
      "sources": [
        # From vendor/freetype/docs/INSTALL.ANY
        # This is for the default config. If we want to customize the config, we
        # need to create a custom ftconfig.h with the appropriate definitions
        # according to vendor/freetype/docs/CUSTOMIZING.

        # base components (required)
        "freetype-2.6.3/src/base/ftsystem.c",
        "freetype-2.6.3/src/base/ftinit.c",
        "freetype-2.6.3/src/base/ftdebug.c",

        "freetype-2.6.3/src/base/ftbase.c",

        "freetype-2.6.3/src/base/ftbbox.c",       # recommended, see <ftbbox.h>
        "freetype-2.6.3/src/base/ftglyph.c",      # recommended, see <ftglyph.h>

        "freetype-2.6.3/src/base/ftbdf.c",        # optional, see <ftbdf.h>
        "freetype-2.6.3/src/base/ftbitmap.c",     # optional, see <ftbitmap.h>
        "freetype-2.6.3/src/base/ftcid.c",        # optional, see <ftcid.h>
        "freetype-2.6.3/src/base/ftfntfmt.c",     # optional, see <ftfntfmt.h>
        "freetype-2.6.3/src/base/ftfstype.c",     # optional
        "freetype-2.6.3/src/base/ftgasp.c",       # optional, see <ftgasp.h>
        "freetype-2.6.3/src/base/ftgxval.c",      # optional, see <ftgxval.h>
        "freetype-2.6.3/src/base/ftlcdfil.c",     # optional, see <ftlcdfil.h>
        "freetype-2.6.3/src/base/ftmm.c",         # optional, see <ftmm.h>
        "freetype-2.6.3/src/base/ftotval.c",      # optional, see <ftotval.h>
        "freetype-2.6.3/src/base/ftpatent.c",     # optional
        "freetype-2.6.3/src/base/ftpfr.c",        # optional, see <ftpfr.h>
        "freetype-2.6.3/src/base/ftstroke.c",     # optional, see <ftstroke.h>
        "freetype-2.6.3/src/base/ftsynth.c",      # optional, see <ftsynth.h>
        "freetype-2.6.3/src/base/fttype1.c",      # optional, see <t1tables.h>
        "freetype-2.6.3/src/base/ftwinfnt.c",     # optional, see <ftwinfnt.h>

        # font drivers (optional; at least one is needed)
        "freetype-2.6.3/src/bdf/bdf.c",           # BDF font driver
        "freetype-2.6.3/src/cff/cff.c",           # CFF/OpenType font driver
        "freetype-2.6.3/src/cid/type1cid.c",      # Type 1 CID-keyed font driver
        "freetype-2.6.3/src/pcf/pcf.c",           # PCF font driver
        "freetype-2.6.3/src/pfr/pfr.c",           # PFR/TrueDoc font driver
        "freetype-2.6.3/src/sfnt/sfnt.c",         # SFNT files support (TrueType & OpenType)
        "freetype-2.6.3/src/truetype/truetype.c", # TrueType font driver
        "freetype-2.6.3/src/type1/type1.c",       # Type 1 font driver
        "freetype-2.6.3/src/type42/type42.c",     # Type 42 font driver
        "freetype-2.6.3/src/winfonts/winfnt.c",   # Windows FONT / FNT font driver

        # rasterizers (optional; at least one is needed for vector formats)
        "freetype-2.6.3/src/raster/raster.c",     # monochrome rasterizer
        "freetype-2.6.3/src/smooth/smooth.c",     # anti-aliasing rasterizer

        # auxiliary modules (optional)
        "freetype-2.6.3/src/autofit/autofit.c",   # auto hinting module
        "freetype-2.6.3/src/cache/ftcache.c",     # cache sub-system (in beta)
        "freetype-2.6.3/src/gzip/ftgzip.c",       # support for compressed fonts (.gz)
        "freetype-2.6.3/src/lzw/ftlzw.c",         # support for compressed fonts (.Z)
        "freetype-2.6.3/src/bzip2/ftbzip2.c",     # support for compressed fonts (.bz2)
        "freetype-2.6.3/src/gxvalid/gxvalid.c",   # TrueTypeGX/AAT table validation
        "freetype-2.6.3/src/otvalid/otvalid.c",   # OpenType table validation
        "freetype-2.6.3/src/psaux/psaux.c",       # PostScript Type 1 parsing
        "freetype-2.6.3/src/pshinter/pshinter.c", # PS hinting module
        "freetype-2.6.3/src/psnames/psnames.c",   # PostScript glyph names support
      ],
      "conditions": [
        [ "OS=='mac'", {
          "sources": [
            "freetype-2.6.3/src/base/ftmac.c",        # only on the Macintosh
          ],
        }],
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "freetype-2.6.3/include",
        ]
      }
    }
  ]
}