#include "root_block.h"

#include "children_block.h"
#include "escaper.h"
#include "layout_entry.h"
#include "style.h"
#include "text_block.h"
#include "writer.h"

Root_Block::Root_Block(Style* style, Escaper* escaper, bool auto_built)
    : Layout_Block(style, auto_built) {
	if (auto_built) {
		this->initialize_from_style_layout(escaper);
	}
}

void Root_Block::initialize_from_style_layout(Escaper* escaper) {
	for (Layout_Entry* layout_entry : this->style->layout_entries()) {
		switch (layout_entry->type()) {
		case Block_Type::Children_Block_E: {
			Children_Block* children_block =
			    (Children_Block*)this->create_block(Block_Type::Children_Block_E);
			children_block->create_block(this->style->default_child_style(), escaper);
			break;
		}
		case Block_Type::Layout_Block_E:
		case Block_Type::Text_Block_E:
			this->create_block(layout_entry->style(), escaper);
			break;
		default:
			error("Not implemented");
		}
	}
}

QString Root_Block::translate() {
	// All layout entries of top level are optional (e.g. header, footer), except the children layout
	// entry In case they are not used, their global variable still need to be initialized, to
	// prevent issue when evalutating the output expression with the Lua VM
	QHash<QString, QString> global_dict = {};
	for (Layout_Entry* layout : this->style->layout_entries()) {
		if (layout->type() != Block_Type::Children_Block_E) {
			global_dict[layout->style()->name()] = "";
		}
	}
	return Layout_Block::translate(global_dict);
}

void Root_Block::save(Writer* writer) {
	Abstract_Multi_Block::save(writer, 0);
}
