#include "multi_block.h"
#include "style.h"

Multi_Block::Multi_Block(Style* style) : Abstract_Block(style) {}

void Multi_Block::Add_Child(Abstract_Block* child) {
	this->first_child.append(child);
}

void Multi_Block::Add_Sibling(Abstract_Block* sibling) {
	this->first_sibling.append(sibling);
}

QString Multi_Block::Backend_Contents() {
	return "";
}
