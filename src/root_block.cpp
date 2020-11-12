#include "root_block.h"

#include "children_block.h"
#include "escaper.h"
#include "layout_entry.h"
#include "style.h"
#include "text_block.h"
#include "writer.h"

Root_Block::Root_Block(Style* style, Escaper* escaper, bool loaded_from_document_file)
    : Layout_Block(style) {
	if (! loaded_from_document_file) {
		this->initialize_from_style_layout(escaper);
	}
}

void Root_Block::initialize_from_style_layout(Escaper* escaper) {
	for (Layout_Entry* layout_entry : this->style->layout_entries()) {
		Block_Type type = Block_Type::Children_Block_E;
		if (! layout_entry->is_children_entry()) {
			type = layout_entry->style()->type();
		}
		switch (type) {
		case Block_Type::Children_Block_E: {
			Children_Block* children_block =
			    (Children_Block*)this->create_block(Block_Type::Children_Block_E);
			if (this->style->default_child_style()->type() == Block_Type::Text_Block_E) {
				Text_Block* text_block = (Text_Block*)children_block->create_block(
				    this->style->default_child_style(), escaper);
				text_block->create_block(Block_Type::Raw_Text_Block_E);
			} else {
				children_block->create_block(this->style->default_child_style());
			}
			break;
		}
		case Block_Type::Layout_Block_E:
			this->create_block(layout_entry->style());
			break;
		case Block_Type::Text_Block_E: {
			Text_Block* tb = (Text_Block*)this->create_block(layout_entry->style(), escaper);
			tb->create_block(Block_Type::Raw_Text_Block_E);
			break;
		}
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
		if (! layout->is_children_entry()) {
			global_dict[layout->style()->name()] = "";
		}
	}
	return Layout_Block::translate(global_dict);
}

void Root_Block::save(Writer* writer) {
	Abstract_Multi_Block::save(writer, 0);
}
