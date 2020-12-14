#include "text_block.h"
#include "raw_text_block.h"
#include "style_properties.h"
#include "styles.h"
#include "writer.h"

Text_Block::Text_Block(Style* style, bool auto_built) : Abstract_Multi_Block(style, auto_built) {
	if (auto_built) {
		this->current_sub_block = (Raw_Text_Block*)this->append_child(Styles::Raw_Text_Style);
	}
}

QString Text_Block::translate(Escaper* escaper) {
	QHash<QString, QString> global_dict = {};
	global_dict[Field::Id::Text_Block] = Abstract_Multi_Block::translate(escaper);
	return this->the_style->properties->translate(global_dict);
}

void Text_Block::save(Writer* writer, int level) {
	writer->write_key(this->the_style->identifier, level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
