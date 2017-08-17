'use strict';

const podofo = require('node-podofo'),
  path = require('path');

let pdf = new podofo.PdfMemDocument(false);
pdf.Load(path.resolve(__dirname , 'valid.pdf'));

console.log(pdf.GetInfo().GetAuthor());