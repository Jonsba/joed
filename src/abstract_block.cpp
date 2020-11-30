#include "abstract_block.h"
#include "field.h"
#include "writer.h"

Abstract_Block::Abstract_Block(Style* style, Abstract_Multi_Block* parent) : The_Style(style) {
	this->the_parent = parent;
}

const Style* Abstract_Block::style() {
	return this->The_Style;
}

Abstract_Multi_Block* Abstract_Block::parent() {
	return this->the_parent;
}

Abstract_Block* Abstract_Block::next() {
	return this->the_next;
}

void Abstract_Block::set_next(Abstract_Block* next) {
	this->the_next = next;
}

Abstract_Block::~Abstract_Block() = default;
