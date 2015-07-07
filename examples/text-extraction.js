var podofo = require('../index');

var pdf = new podofo.PdfMemDocument();
pdf.Load('/tmp/yanrong.pdf');
var tokenizer = new podofo.PdfContentsTokenizer(pdf.GetPage(0));

var texts = [];
var inTextBlock = false;
var textInCurrentBlock = [];
var token = true;
var stack;

while (token) {
  token = tokenizer.ReadNext();
  switch (token.type) {
  case podofo.ePdfContentsType_Keyword:
    switch (token.keyword) {
    case 'BT':
      inTextBlock = true;
      stack = [];
      break;
    case 'ET':
      inTextBlock = false;
      texts.push(textInCurrentBlock.join(''));
      textInCurrentBlock = [];
      break;
    case 'Tf':
    case 'Td':
    case 'TD':
      texts.push(textInCurrentBlock.join(''));
      textInCurrentBlock = [];
      break;
    case 'Tj':
    case '\'':
    case '"':
      textInCurrentBlock.push(stack.pop().GetString());
      break;
    case 'TJ':
      stack.pop().GetArray().forEach(function (obj) {
        if (obj.IsString()) {
          textInCurrentBlock.push(obj.GetString());
        }
      });
      break;
    }

    break;
  case podofo.ePdfContentsType_Variant:
  case podofo.ePdfContentsType_ImageData:
    if (inTextBlock) {
      stack.push(token.variant);
    }
    break;
  }
}

console.log(texts
    .map(Function.prototype.call, String.prototype.trim)
    .filter(function (text) { return text; })
);

