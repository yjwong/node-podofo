# Node-Podofo

[![Build Status](https://api.travis-ci.org/MatthD/node-podofo.svg?branch=master)](https://travis-ci.org/MatthD/node-podofo)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/matthd/node-podofo?svg=true)](https://ci.appveyor.com/project/MatthD/node-podofo)

Node-podofo in a Node addons written in C++ to manipulate & read PDF files (create pdf, get metadata, information, author, get text from pdf ...).

This is an updated fork of [podofo]()

# Why this fork ?

This fork compile 3 years of podofo dev (from 0.9.3 to 0.9.5)
And it add the possibility to DISABLE DEBUG & LOG by default which was really terrible when using with Node.js

# Why Node-podofo

Of course you can use pdfjs in full js, but if speed & error catcher are important for you node-podofo is here. 

Because it's a native addons written in C++, it is very speed & you can use the function directly in your project just like all npm module.

It's not just a spawn of a command so error, returned value .. can be managed in Javascript as easy as pie.

It fully intregates all require Libraries, nothing to install more.


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

# Using with node 


```javascript
const podofo = require('podofo');

let pdf = new podofo.PdfMemDocument(false);
pdf.Load('/path/to/a/file.pdf');

console.log(pdf.GetInfo().GetAuthor());
// Will return software author
```


# Building on Windows

PoDoFo (minimally) depends on zlib and freetype. You will also need the source
for PoDoFo itself. You can download these packages and extract them into `deps/`.

After extraction, the directory tree should look like this:

> - deps/
>   - freetype/
>   - podofo/
>   - zlib/

The following versions have been tested:

- freetype: 2.8
- podofo: 0.9.5
- zlib: 1.2.11

Then you just need to run `node-pre-gyp configure build` to obtain a binary.

Of course, you will also need to have a toolchain installed. This has been tested
with Visual Studio 2015. The Community edition is available from Microsoft for
free.

# Examples

You can exec a simple GetAuthor() & text-extractor:

From your main module(main-module/node_modules/node-podofo) just launch:

    node node_modules/node-podofo/index.js

# Dev

To complie from source node-podofo just :

    git submodule init
    git submodule update
    npm install --build-from-source

This will recreate the bin in ./lib


# Debug & Logs

By default log & debug are disable, to enable them when you can just pass `true` option to PdfMemDocument as:

`var pdf = new podofo.PdfMemDocument(true);`

# Notice

All Podofo Classes cannot be used directly, for example, PdfError could be called only via c++, not javascript binding.
If you want to update this fork, you must know about c++/Node.js, podofo, node-addons, Nan V8, node-pre-gyp, node-pre-gyp-github & use travis for build for OSX+Linux and Appveyor to build for Windows.

