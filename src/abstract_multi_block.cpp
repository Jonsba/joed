#include "abstract_multi_block.h"

Abstract_Multi_Block::Abstract_Multi_Block(QString Identifier, Block_Type Type)
    : Abstract_Block(Identifier, Type) {}

void Abstract_Multi_Block::add_block(Abstract_Block* child) {
	this->the_blocks.append(child);
}

QLinkedList<Abstract_Block*> Abstract_Multi_Block::blocks() {
	return this->the_blocks;
}
