#include "abstract_block.h"
#include "style.h"

Abstract_Block::Abstract_Block(Style* style) {
	this->the_style = style;
}

Style* Abstract_Block::style() {
	return this->the_style;
}
