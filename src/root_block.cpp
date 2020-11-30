#include "root_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "style_properties.h"
#include "styles.h"
#include "text_block.h"
#include "writer.h"

Root_Block::Root_Block(Style* style, bool auto_built) : Layout_Block(style, nullptr, auto_built) {
	if (auto_built) {
		this->initialize_from_style_layout();
	}
}

void Root_Block::initialize_from_style_layout() {
	for (Layout_Entry* layout_entry : this->The_Style->properties->layout_entries()) {
		switch (layout_entry->style()->type) {
		case Style_Type::Children_E: {
			Children_Block* children_block =
			    (Children_Block*)this->create_block(Styles::Children_Style);
			children_block->create_block(this->The_Style->properties->default_child_style());
			break;
		}
		case Style_Type::Layouted_E:
		case Style_Type::Text_E:
			this->create_block(layout_entry->style());
			break;
		default:
			throw Exceptions::Not_Implemented();
		}
	}
}

QString Root_Block::translate(Escaper* escaper) {
	// All layout entries of top level are optional (e.g. header, footer), except the children layout
	// entry In case they are not used, their global variable still need to be initialized, to
	// prevent issue when evalutating the output expression with the Lua VM
	QHash<QString, QString> global_dict = {};
	for (Layout_Entry* layout : this->The_Style->properties->layout_entries()) {
		if (layout->style()->type != Style_Type::Children_E) {
			global_dict[layout->style()->identifier] = "";
		}
	}
	return Layout_Block::translate(escaper, global_dict);
}

void Root_Block::save(Writer* writer) {
	writer->write_key(Field::Key::Document, 0);
	Abstract_Multi_Block::save(writer, 1);
}
