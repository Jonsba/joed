#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_non_layouted_block.h"
#include "i_styled_block.h"

class Text_Block : public Abstract_Non_Layouted_Block, I_Styled_Block {
 public:
	Text_Block(Style* style);
	QString to_backend_code();
};

#endif // TEXT_BLOCK_H
