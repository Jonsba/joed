#include "layout_block.h"
#include "children_block.h"
#include "layout_entry.h"
#include "raw_text_block.h"
#include "style_properties.h"
#include "styles.h"
#include "text_block.h"
#include "writer.h"

Layout_Block::Layout_Block(Style* style, bool auto_built)
    : Abstract_Multi_Block(style, auto_built) {
	if (auto_built) {
		for (Layout_Entry* layout_entry : this->the_style->properties->layout_entries()) {
			switch (layout_entry->style()->type) {
			case Style_Type::Children: {
				Children_Block* children_block =
				    (Children_Block*)this->append_child(Styles::Children_Style);
				children_block->append_default_child();
				break;
			}
			case Style_Type::Layouted:
			case Style_Type::Text:
				this->append_child(layout_entry->style());
				break;
			default:
				throw Exceptions::Not_Implemented();
			}
		}
	}
}

QString Layout_Block::translate(Escaper* escaper) {
	return this->translate(escaper, {});
}

QString Layout_Block::translate(Escaper* escaper, QHash<QString, QString> global_dict) {
	for (Abstract_Block* block = this->first_child(); block != nullptr; block = block->next()) {
		global_dict[block->style()->identifier] = block->translate(escaper);
	}
	return this->the_style->properties->translate(global_dict);
}

void Layout_Block::save(Writer* writer, int level) {
	writer->write_key(this->the_style->identifier, level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
