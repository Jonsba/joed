#include "children_block.h"
#include "field.h"
#include "joed.h"
#include "layout_block.h"
#include "style_properties.h"
#include "styles.h"
#include "text_block.h"

Children_Block::Children_Block(bool auto_built)
    : Abstract_Multi_Block(Styles::Children_Style, auto_built) {}

void Children_Block::append_default_child() {
	this->append_child(this->parent()->style()->properties->default_child_style());
}

Abstract_Multi_Block* Children_Block::insert_default_child(Abstract_Block* first_sub_block,
                                                           Abstract_Block* sibling,
                                                           bool insert_after) {
	Style* style = this->parent()->style()->properties->default_child_style();
	auto block = (Abstract_Multi_Block*)sibling->insert_sibling(style, insert_after, false);
	block->append_child(first_sub_block);
	return block;
}
