#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_non_layouted_block.h"

class Style;

class Text_Block : public Abstract_Non_Layouted_Block {
 public:
	Text_Block(Style* style);
	QString translate();

 private:
	Style* style;
};

#endif // TEXT_BLOCK_H
