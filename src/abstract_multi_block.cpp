#include "abstract_multi_block.h"
#include "styles.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(Style* style, Abstract_Multi_Block* parent,
                                           bool auto_built)
    : Abstract_Block(style, parent) {
	this->auto_built = auto_built;
	this->Blocks_Identifier = Field::Key::Blocks;
	if (style->type == Style_Type::Children_E) {
		this->Blocks_Identifier = Field::Id::Children;
	}
}

void Abstract_Multi_Block::add_child(Abstract_Block* child) {
	if (this->last_child == nullptr) {
		this->last_child = child;
		this->the_first_child = child;
		return;
	}
	this->last_child->set_next(child);
	this->last_child = child;
}

Abstract_Block* Abstract_Multi_Block::first_child() {
	return this->the_first_child;
}

QString Abstract_Multi_Block::translate(Escaper* escaper) {
	QStringList child_contents;
	for (Abstract_Block* block = this->the_first_child; block != nullptr; block = block->next()) {
		child_contents.append(block->translate(escaper));
	}
	return child_contents.join("\n");
}

void Abstract_Multi_Block::save(Writer* writer, int level) {
	writer->write_key(this->Blocks_Identifier, level);
	for (Abstract_Block* block = this->the_first_child; block != nullptr; block = block->next()) {
		block->save(writer, level + 1);
	}
}

Abstract_Multi_Block::~Abstract_Multi_Block() {
	for (Abstract_Block* block = this->the_first_child; block != nullptr; block = block->next()) {
		delete block;
	}
}
