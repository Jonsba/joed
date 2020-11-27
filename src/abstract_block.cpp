#include "abstract_block.h"
#include "field.h"
#include "writer.h"

Abstract_Block::Abstract_Block(Style* style) : The_Style(style) {}

const Style* Abstract_Block::style() {
	return this->The_Style;
}

Abstract_Block::~Abstract_Block() = default;
