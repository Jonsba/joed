#include "multi_block.h"
#include "joed.h"
#include "style.h"

Multi_Block::Multi_Block(Style* style) : Abstract_Block(style) {}

void Multi_Block::Add_Child(Abstract_Block* child) {
	this->first_child.append(child);
}

QString Multi_Block::Compile() {
	QString child_contents = "";
	for (Abstract_Block* child_block : this->first_child) {
		child_contents += child_block->Compile();
	}
	return this->style->Compile(Children_Block_Value, child_contents);
}
