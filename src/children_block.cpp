#include "children_block.h"
#include "layout_block.h"
#include "text_block.h"
#include "writer.h"

Children_Block::Children_Block(bool auto_built)
    : Abstract_Non_Layouted_Block(Children_Block_Id, Block_Type::Children_Block_E, auto_built) {}

Abstract_Block* Children_Block::create_block(Block_Type type, Style* style, Escaper* escaper) {
	Abstract_Multi_Block* new_block;
	switch (type) {
	case Block_Type::Layout_Block_E: {
		new_block = new Layout_Block(style, this->auto_built);
		break;
	}
	case Block_Type::Text_Block_E: {
		new_block = new Text_Block(style, escaper, this->auto_built);
		break;
	}
	default:
		error("Not implemented!");
	}
	this->add_block(new_block);
	return new_block;
}

QString Children_Block::translate() {
	return Abstract_Non_Layouted_Block::translate();
}

void Children_Block::save(Writer* writer, int level) {
	writer->write_key(Joed::Keys[Children_E], level);
	for (Abstract_Block* block : this->the_blocks) {
		block->save(writer, level + 1);
	}
}
