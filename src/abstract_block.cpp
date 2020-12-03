#include "abstract_block.h"
#include "children_block.h"
#include "exceptions.h"
#include "layout_block.h"
#include "raw_text_block.h"
#include "text_block.h"

Abstract_Block::Abstract_Block(Style* style) {
	this->the_style = style;
}

Style* Abstract_Block::style() {
	return this->the_style;
}

Abstract_Block* Abstract_Block::next() {
	return this->the_next;
}

Abstract_Block* Abstract_Block::insert_sibling(Style* style, bool auto_built) {
	Abstract_Block* new_block = make_block(style, auto_built);
	this->insert_sibling(new_block);
	return new_block;
}

void Abstract_Block::insert_sibling(Abstract_Block* block) {
	Abstract_Block* next_block = this->next();
	this->the_next = block;
	block->the_next = next_block;
}

Abstract_Block* Abstract_Block::make_block(Style* style, bool auto_built) {
	Abstract_Block* new_block;
	switch (style->type) {
	case Style_Type::Children: {
		new_block = new Children_Block(auto_built);
		break;
	}
	case Style_Type::Layouted: {
		new_block = new Layout_Block(style, auto_built);
		break;
	}
	case Style_Type::Text: {
		new_block = new Text_Block(style, auto_built);
		break;
	}
	case Style_Type::Raw_Text: {
		new_block = new Raw_Text_Block();
		break;
	}
	case Style_Type::Undefined:
		throw Exception("Style '" + style->identifier + "' has an undefined type");
	}
	return new_block;
}

Abstract_Block::~Abstract_Block() = default;
