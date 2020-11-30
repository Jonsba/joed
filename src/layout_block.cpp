#include "layout_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "raw_text_block.h"
#include "style_properties.h"
#include "text_block.h"
#include "writer.h"

Layout_Block::Layout_Block(Style* style, Abstract_Multi_Block* parent, bool auto_built)
    : Abstract_Multi_Block(style, parent, auto_built) {}

Abstract_Block* Layout_Block::create_block(Style* style) {
	Abstract_Multi_Block* new_block;
	switch (style->type) {
	case Style_Type::Children_E: {
		new_block = new Children_Block(this, this->auto_built);
		break;
	}
	case Style_Type::Layouted_E: {
		new_block = new Layout_Block(style, this, this->auto_built);
		break;
	}
	case Style_Type::Text_E: {
		new_block = new Text_Block(style, this, this->auto_built);
		break;
	}
	default:
		throw Exception("Style '" + style->identifier + "' has an unsupported type");
	}
	this->add_child(new_block);
	return new_block;
}

QString Layout_Block::translate(Escaper* escaper) {
	return this->translate(escaper, {});
}

QString Layout_Block::translate(Escaper* escaper, QHash<QString, QString> global_dict) {
	for (Abstract_Block* block = this->first_child(); block != nullptr; block = block->next()) {
		global_dict[block->style()->identifier] = block->translate(escaper);
	}
	return this->The_Style->properties->translate(global_dict);
}

void Layout_Block::save(Writer* writer, int level) {
	writer->write_key(this->The_Style->identifier, level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
