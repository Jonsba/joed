#include "layout_block.h"
#include "abstract_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "lua_vm.h"
#include "raw_text_block.h"
#include "style.h"
#include "text_block.h"

Layout_Block::Layout_Block(Style* style, bool loaded_from_document_file)
    : Abstract_Multi_Block(style->name(), style->type()), I_Styled_Block(style) {
	if (! loaded_from_document_file) {
		this->initialize_from_style_layout();
	}
}

void Layout_Block::initialize_from_style_layout() {

	for (Layout_Entry* layout_entry : this->style()->layout_entries()) {
		Abstract_Block* new_block;
		if (layout_entry->is_children_entry()) {
			Children_Block* children_block = new Children_Block();
			children_block->add_block(this->create_sub_block(this->style()->default_child_style()));
			new_block = (Abstract_Block*)children_block;
		} else {
			new_block = this->create_sub_block(layout_entry->style());
		}
		this->add_block(new_block);
	}
}

Abstract_Block* Layout_Block::create_sub_block(Style* style) {
	Abstract_Block* new_block;
	switch (style->type()) {
	case Layout_Block_E:
		new_block = new Layout_Block(style);
		break;
	case Text_Block_E: {
		Text_Block* text_block = new Text_Block(style);
		text_block->add_block(new Raw_Text_Block());
		new_block = (Abstract_Block*)text_block;
		break;
	}
	default:
		error("Not implemented!");
	}
	return new_block;
}

QString Layout_Block::to_backend_code() {
	Global_Dict global_dict;
	for (Abstract_Block* child_block : this->the_blocks) {
		global_dict[child_block->identifier()] = child_block->to_backend_code();
	}
	return this->the_style->compile(global_dict);
}
