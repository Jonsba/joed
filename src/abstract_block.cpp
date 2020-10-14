#include "abstract_block.h"

Abstract_Block::Abstract_Block(Style* style) {
	this->style = style;
}

Style* Abstract_Block::Get_Style() {
	return this->style;
}
