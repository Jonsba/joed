#include "children_block.h"
#include "joed.h"
#include "layout_block.h"
#include "text_block.h"
#include "writer.h"

Children_Block::Children_Block(bool auto_built)
    : Abstract_Multi_Block(Field::Id::Children_Block, Children_Block_Type, auto_built) {}

Abstract_Block* Children_Block::create_block(Block_Type type, Style* style, Escaper* escaper) {
	Abstract_Multi_Block* new_block;
	switch (type.base) {
	case Block_Base_Type::Layout_Block_E: {
		new_block = new Layout_Block(style, this->auto_built);
		break;
	}
	case Block_Base_Type::Text_Block_E: {
		new_block = new Text_Block(style, escaper, this->auto_built);
		break;
	}
	default:
		error("Not implemented!");
	}
	this->add_block(new_block);
	return new_block;
}
