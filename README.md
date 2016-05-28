# Bindings for the PoDoFo PDF Library

This project provides Node.js bindings for the [PoDoFo](http://podofo.sourceforge.net/)
PDF library.

Basic functionality has been implemented, but this is generally a work in
progress. Pull requests are welcome.

## Installing

This requires `libpodofo` to be installed. If you are using Ubuntu, the
following command should suffice:

    sudo apt-get install libpodofo-dev

Then, installing this library is as simple as:

    npm install podofo

# Building on Windows

PoDoFo (minimally) depends on zlib and freetype. You will also need the source
for PoDoFo itself. You can download these packages and extract them into `deps/`.

After extraction, the directory tree should look like this:

> - deps/
>   - freetype/
>   - podofo/
>   - zlib/

The following versions have been tested:

- freetype: 2.6.3
- podofo: 0.9.3
- zlib: 1.2.8

Then you just need to run `node-pre-gyp configure build` to obtain a binary.

Of course, you will also need to have a toolchain installed. This has been tested
with Visual Studio 2015. The Community edition is available from Microsoft for
free.
