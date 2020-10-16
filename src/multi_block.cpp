#include "multi_block.h"
#include "joed.h"
#include "style.h"

Multi_Block::Multi_Block(Style* style) : Abstract_Block(style) {}

void Multi_Block::add_child(Abstract_Block* child) {
	this->first_child.append(child);
}

QString Multi_Block::compile() {
	QString child_contents = "";
	for (Abstract_Block* child_block : this->first_child) {
		child_contents += child_block->compile();
	}
	return this->the_style->compile(Children_Block_Value, child_contents);
}
