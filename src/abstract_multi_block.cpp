#include "abstract_multi_block.h"
#include "styles.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(Style* style, Abstract_Multi_Block* parent,
                                           bool auto_built)
    : Abstract_Block(style, parent) {
	this->auto_built = auto_built;
}

Abstract_Block* Abstract_Multi_Block::append_child(Style* style) {
	Abstract_Block* new_block = this->make_block(style, this, this->auto_built);
	this->append_child(new_block);
	return new_block;
}

void Abstract_Multi_Block::append_child(Abstract_Block* block) {
	if (this->last_child_tmp == nullptr) {
		this->last_child_tmp = block;
		this->the_first_child = block;
		return;
	}
	this->last_child_tmp->insert_sibling(block, true);
	this->last_child_tmp = block;
}

Abstract_Block* Abstract_Multi_Block::first_child() {
	return this->the_first_child;
}

void Abstract_Multi_Block::reset_first_child(Abstract_Block* new_first_child) {
	this->the_first_child = new_first_child;
}

QString Abstract_Multi_Block::translate(Escaper* escaper) {
	QStringList child_contents;
	for (Abstract_Block* block = this->the_first_child; block != nullptr; block = block->next()) {
		child_contents.append(block->translate(escaper));
	}
	return child_contents.join("\n");
}

void Abstract_Multi_Block::save(Writer* writer, int level) {
	QString blocks_identifier = Field::Key::Blocks;
	if (this->style()->type == Style_Type::Children) {
		blocks_identifier = Field::Id::Children;
	}
	writer->write_key(blocks_identifier, level);
	for (Abstract_Block* block = this->first_child(); block != nullptr; block = block->next()) {
		block->save(writer, level + 1);
	}
}

Abstract_Multi_Block::~Abstract_Multi_Block() {
	// No possible access to the next field once the block is deleted, so we need to loop differently
	Abstract_Block* block = this->first_child();
	while (block != nullptr) {
		Abstract_Block* next_block = block->next();
		delete block;
		block = next_block;
	}
}
