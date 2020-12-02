#include "abstract_multi_block.h"
#include "styles.h"
#include "writer.h"

Abstract_Multi_Block::Abstract_Multi_Block(Style* style, bool auto_built) : Abstract_Block(style) {
	this->auto_built = auto_built;
	this->Blocks_Identifier = Field::Key::Blocks;
	if (style->type == Style_Type::Children_E) {
		this->Blocks_Identifier = Field::Id::Children;
	}
}

Abstract_Block* Abstract_Multi_Block::append_child(Style* style) {
	Abstract_Block* new_block = this->make_block(style, this->auto_built);
	this->append_child(new_block);
	return new_block;
}

void Abstract_Multi_Block::append_child(Abstract_Block* block) {
	if (this->last_child == nullptr) {
		this->last_child = block;
		this->the_first_child = block;
		return;
	}
	// When Abstract_Block::add_sibling is called, it won't update the parent's last_child pointer,
	// therefore we need to make sure it points to the right element
	while (this->last_child->the_next != nullptr) {
		this->last_child = this->last_child->the_next;
	}
	this->last_child->the_next = block;
	this->last_child = block;
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
