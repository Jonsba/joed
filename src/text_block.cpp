#include "text_block.h"
#include "raw_text_block.h"
#include "style.h"
#include "writer.h"

Text_Block::Text_Block(Style* style, bool auto_built)
    : Abstract_Multi_Block(style->name(), style->type(), auto_built) {
	this->style = style;
	if (auto_built) {
		this->current_sub_block = (Raw_Text_Block*)this->create_block(Raw_Text_Block_Type);
	}
}

Abstract_Block* Text_Block::create_block(Block_Type type, Style* style) {
	Abstract_Block* new_block;
	switch (type.base) {
	case Block_Base_Type::Raw_Text_Block_E: {
		new_block = new Raw_Text_Block();
		break;
	}
	default:
		error("Not implemented!");
	}
	this->add_block(new_block);
	return new_block;
}

QString Text_Block::translate(Escaper* escaper) {
	QHash<QString, QString> global_dict = {};
	global_dict[Field::Id::Text_Content] = Abstract_Multi_Block::translate(escaper);
	return this->style->translate(global_dict);
}

void Text_Block::save(Writer* writer, int level) {
	writer->write_key(this->style->name(), level);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
