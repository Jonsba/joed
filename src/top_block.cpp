#include "top_block.h"
#include "layout_entry.h"
#include "style.h"

Top_Block::Top_Block(Style* style, bool loaded_from_document_file)
    : Layout_Block(style, loaded_from_document_file) {}

QString Top_Block::translate() {
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
