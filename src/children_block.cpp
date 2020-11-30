#include "children_block.h"
#include "field.h"
#include "joed.h"
#include "layout_block.h"
#include "styles.h"
#include "text_block.h"

Children_Block::Children_Block(Abstract_Multi_Block* parent, bool auto_built)
    : Abstract_Multi_Block(Styles::Children_Style, parent, auto_built) {}

Abstract_Block* Children_Block::create_block(Style* style) {
	Abstract_Multi_Block* new_block;
	switch (style->type) {
	case Style_Type::Layouted_E: {
		new_block = new Layout_Block(style, this, this->auto_built);
		break;
	}
	case Style_Type::Text_E: {
		new_block = new Text_Block(style, this, this->auto_built);
		break;
	}
	default:
		throw Exceptions::Not_Implemented();
	}
	this->add_child(new_block);
	return new_block;
}
