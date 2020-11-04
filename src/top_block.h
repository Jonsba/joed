#ifndef TOP_BLOCK_H
#define TOP_BLOCK_H

#include "layout_block.h"

class Style;
class Escaper;

class Top_Block : public Layout_Block {
 public:
	Top_Block(Style* style, Escaper* escaper, bool loaded_from_document_file = true);
	QString translate();

 private:
	Escaper* escaper;
};

#endif // TOP_BLOCK_H
