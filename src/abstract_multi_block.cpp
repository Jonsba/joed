#include "abstract_multi_block.h"
#include "style.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(QString identifier, Block_Type type)
    : Abstract_Block(identifier, type) {}

Abstract_Block* Abstract_Multi_Block::create_block(Block_Type type) {
	return this->create_block(type, nullptr, nullptr);
}

Abstract_Block* Abstract_Multi_Block::create_block(Style* style) {
	return this->create_block(style->type(), style, nullptr);
}

Abstract_Block* Abstract_Multi_Block::create_block(Style* style, Escaper* escaper) {
	return this->create_block(style->type(), style, escaper);
}

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

Abstract_Multi_Block::~Abstract_Multi_Block() {
	for (Abstract_Block* block : this->the_blocks) {
		delete block;
	}
}
