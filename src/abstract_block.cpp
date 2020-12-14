#include "abstract_block.h"
#include "children_block.h"
#include "exceptions.h"
#include "layout_block.h"
#include "raw_text_block.h"
#include "style.h"
#include "text_block.h"

Abstract_Block::Abstract_Block(Style* style) {
	this->the_style = style;
}

Style* Abstract_Block::style() {
	return this->the_style;
}

Abstract_Multi_Block* Abstract_Block::parent() {
	return this->the_parent;
}

void Abstract_Block::set_parent(Abstract_Multi_Block* parent) {
	this->the_parent = parent;
}

Abstract_Block* Abstract_Block::next() {
	return this->the_next;
}

Abstract_Block* Abstract_Block::insert_sibling(Style* style, bool insert_after, bool auto_built) {
	Abstract_Block* new_block = make_block(style, auto_built);
	this->insert_sibling(new_block, insert_after);
	return new_block;
}

void Abstract_Block::insert_sibling(Abstract_Block* block, bool insert_after) {
	block->set_parent(this->parent());
	if (insert_after) {
		this->set_sibling_relationship(this, block);
	} else {
		if (this->previous != nullptr) {
			this->set_sibling_relationship(this->previous, block);
		} else { // To be inserted as the first sibling?
			block->the_next = this;
			this->previous = block;
			this->the_parent->reset_first_child(block);
		}
	}
}

void Abstract_Block::set_sibling_relationship(Abstract_Block* first, Abstract_Block* second) {
	Abstract_Block* third = first->the_next;
	first->the_next = second;
	second->previous = first;
	second->the_next = third;
	if (third != nullptr) { // If the second block isn't the last block
		third->previous = second;
	}
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
