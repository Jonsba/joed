#include "root_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "style.h"
#include "text_block.h"
#include "writer.h"

Root_Block::Root_Block(Style* style, bool auto_built) : Layout_Block(style, auto_built) {
	if (auto_built) {
		this->initialize_from_style_layout();
	}
}

void Root_Block::initialize_from_style_layout() {
	for (Layout_Entry* layout_entry : this->style->layout_entries()) {
		switch (layout_entry->type().base) {
		case Block_Base_Type::Children_Block_E: {
			Children_Block* children_block = (Children_Block*)this->create_block(Children_Block_Type);
			children_block->create_block(this->style->default_child_style());
			break;
		}
		case Block_Base_Type::Layout_Block_E:
		case Block_Base_Type::Text_Block_E:
			this->create_block(layout_entry->style());
			break;
		default:
			error("Not implemented");
		}
	}
}

QString Root_Block::translate(Escaper* escaper) {
	// All layout entries of top level are optional (e.g. header, footer), except the children layout
	// entry In case they are not used, their global variable still need to be initialized, to
	// prevent issue when evalutating the output expression with the Lua VM
	QHash<QString, QString> global_dict = {};
	for (Layout_Entry* layout : this->style->layout_entries()) {
		if (layout->type().base != Block_Base_Type::Children_Block_E) {
			global_dict[layout->style()->name()] = "";
		}
	}
	return Layout_Block::translate(escaper, global_dict);
}

void Root_Block::save(Writer* writer) {
	writer->write_key(Field::Key::Document, 0);
	Abstract_Multi_Block::save(writer, 1);
}
