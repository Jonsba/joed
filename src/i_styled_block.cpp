#include "i_styled_block.h"

I_Styled_Block::I_Styled_Block(Style* the_style) {
	this->the_style = the_style;
}

Style* I_Styled_Block::style() {
	return this->the_style;
}
