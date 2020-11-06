#include "abstract_multi_block.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(QString identifier, Block_Type type)
    : Abstract_Block(identifier, type) {}

void Abstract_Multi_Block::add_block(Abstract_Block* child) {
	this->the_blocks.append(child);
}

QLinkedList<Abstract_Block*> Abstract_Multi_Block::blocks() {
	return this->the_blocks;
}

void Abstract_Multi_Block::save(Writer* writer, int level) {
	writer->write_key(Joed::Keys[Content_E], level);
	for (Abstract_Block* block : this->the_blocks) {
		block->save(writer, level + 1);
	}
}
