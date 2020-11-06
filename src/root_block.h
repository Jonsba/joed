#ifndef ROOT_BLOCK_H
#define ROOT_BLOCK_H

#include "layout_block.h"

class Style;
class Escaper;
class Writer;

class Root_Block : public Layout_Block {
 public:
	Root_Block(Style* style, Escaper* escaper, bool loaded_from_document_file = true);
	void save(Writer* writer);
	QString translate();
};

#endif // ROOT_BLOCK_H
