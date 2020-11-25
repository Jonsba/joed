#include "layout_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "raw_text_block.h"
#include "style_properties.h"
#include "text_block.h"
#include "writer.h"

Layout_Block::Layout_Block(Style* style, bool auto_built)
    : Abstract_Multi_Block(style, auto_built) {}

Abstract_Block* Layout_Block::create_block(Style* style) {
	Abstract_Multi_Block* new_block;
	switch (style->type) {
	case Style_Type::Children_E: {
		new_block = new Children_Block(this->auto_built);
		break;
	}
	case Style_Type::Layouted_E: {
		new_block = new Layout_Block(style, this->auto_built);
		break;
	}
	case Style_Type::Text_E: {
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
		global_dict[child_block->style()->identifier] = child_block->translate(escaper);
	}
	return this->The_Style->properties->translate(global_dict);
}

void Layout_Block::save(Writer* writer, int level) {
	writer->write_key(this->The_Style->identifier, level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
