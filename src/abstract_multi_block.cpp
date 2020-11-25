#include "abstract_multi_block.h"
#include "style_properties.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(Style* style, bool auto_built) : Abstract_Block(style) {
	this->auto_built = auto_built;
	this->Blocks_Identifier = Field::Key::Blocks;
	if (style->type == Style_Type::Children_E) {
		this->Blocks_Identifier = Field::Key::Children;
	}
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
