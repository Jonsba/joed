#ifndef TOP_BLOCK_H
#define TOP_BLOCK_H

#include "layout_block.h"

class Style;

class Top_Block : public Layout_Block {
 public:
	Top_Block(Style* style, bool loaded_from_document_file = true);
	QString translate();
};

#endif // TOP_BLOCK_H
