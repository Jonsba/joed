#include "abstract_multi_block.h"
#include "style.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(QString identifier, Block_Type type, bool auto_built)
    : Abstract_Block(identifier, type) {
	this->auto_built = auto_built;
	this->Blocks_Identifier = Field::Key::Blocks;
	if (type.base == Block_Base_Type::Children_Block_E) {
		this->Blocks_Identifier = Field::Key::Children;
	}
}

Abstract_Block* Abstract_Multi_Block::create_block(Block_Type type) {
	return this->create_block(type, nullptr);
}

Abstract_Block* Abstract_Multi_Block::create_block(Style* style) {
	return this->create_block(style->type(), style);
}

void Abstract_Multi_Block::add_block(Abstract_Block* child) {
	this->the_blocks.append(child);
}

QLinkedList<Abstract_Block*> Abstract_Multi_Block::blocks() {
	return this->the_blocks;
}

QString Abstract_Multi_Block::translate(Escaper* escaper) {
	QStringList child_contents;
	for (Abstract_Block* child_block : this->the_blocks) {
		child_contents.append(child_block->translate(escaper));
	}
	return child_contents.join("\n");
}

void Abstract_Multi_Block::save(Writer* writer, int level) {
	writer->write_key(this->Blocks_Identifier, level);
	for (Abstract_Block* block : this->the_blocks) {
		block->save(writer, level + 1);
	}
}

Abstract_Multi_Block::~Abstract_Multi_Block() {
	for (Abstract_Block* block : this->the_blocks) {
		delete block;
	}
}
