#include "layout_block.h"
#include "abstract_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "raw_text_block.h"
#include "style.h"
#include "text_block.h"
#include "writer.h"

Layout_Block::Layout_Block(Style* style, bool auto_built)
    : Abstract_Multi_Block(style->name(), style->type(), auto_built) {
	this->style = style;
}

Abstract_Block* Layout_Block::create_block(Block_Type type, Style* style) {
	Abstract_Multi_Block* new_block;
	switch (type.base) {
	case Block_Base_Type::Children_Block_E: {
		new_block = new Children_Block(this->auto_built);
		break;
	}
	case Block_Base_Type::Layout_Block_E: {
		new_block = new Layout_Block(style, this->auto_built);
		break;
	}
	case Block_Base_Type::Text_Block_E: {
		new_block = new Text_Block(style, this->auto_built);
		break;
	}
	default:
		error("Not implemented!");
	}
	this->add_block(new_block);
	return new_block;
}

QString Layout_Block::translate(Escaper* escaper) {
	return this->translate(escaper, {});
}

QString Layout_Block::translate(Escaper* escaper, QHash<QString, QString> global_dict) {
	for (Abstract_Block* child_block : this->the_blocks) {
		global_dict[child_block->identifier()] = child_block->translate(escaper);
	}
	return this->style->translate(global_dict);
}

void Layout_Block::save(Writer* writer, int level) {
	writer->write_key(this->style->name(), level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
