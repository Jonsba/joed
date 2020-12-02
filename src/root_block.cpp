#include "root_block.h"
#include "layout_entry.h"
#include "style_properties.h"
#include "writer.h"

Root_Block::Root_Block(Style* style, bool auto_built) : Layout_Block(style, auto_built) {}

QString Root_Block::translate(Escaper* escaper) {
	// All layout entries of top level are optional (e.g. header, footer), except the children layout
	// entry In case they are not used, their global variable still need to be initialized, to
	// prevent issue when evalutating the output expression with the Lua VM
	QHash<QString, QString> global_dict = {};
	for (Layout_Entry* layout : this->the_style->properties->layout_entries()) {
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
