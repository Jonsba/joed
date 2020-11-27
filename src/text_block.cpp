#include "text_block.h"
#include "raw_text_block.h"
#include "style_properties.h"
#include "styles.h"
#include "writer.h"

Text_Block::Text_Block(Style* style, bool auto_built) : Abstract_Multi_Block(style, auto_built) {
	if (auto_built) {
		this->current_sub_block = (Raw_Text_Block*)this->create_block(Styles::Raw_Text_Style);
	}
}

Abstract_Block* Text_Block::create_block(Style* style) {
	Abstract_Block* new_block;
	switch (style->type) {
	case Style_Type::Raw_Text_E: {
		new_block = new Raw_Text_Block();
		break;
	}
	default:
		throw Exceptions::Not_Implemented();
	}
	this->add_block(new_block);
	return new_block;
}

QString Text_Block::translate(Escaper* escaper) {
	QHash<QString, QString> global_dict = {};
	global_dict[Field::Id::Text_Block] = Abstract_Multi_Block::translate(escaper);
	return this->The_Style->properties->translate(global_dict);
}

void Text_Block::save(Writer* writer, int level) {
	writer->write_key(this->The_Style->identifier, level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
