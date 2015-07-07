var podofo = require('../index');

var pdf = new podofo.PdfMemDocument();
pdf.Load('/tmp/business-resume.pdf');

/**
 * Returns the extracted text for a page.
 */
var getTextsForPage = function (page) {
  var tokenizer = new podofo.PdfContentsTokenizer(pdf.GetPage(page));

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
      case 'T*':
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

  return texts
      .map(Function.prototype.call, String.prototype.trim)
      .filter(function (text) { return text; });
};

var numPages = pdf.GetPageCount();
for (var i = 0; i < numPages; i++) {
  console.log(getTextsForPage(i));
}

