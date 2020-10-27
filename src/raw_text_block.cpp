#include "raw_text_block.h"

Raw_Text_Block::Raw_Text_Block(QString text)
    : Abstract_Block(Raw_Text_Block_Id, Block_Type::Raw_Text_Block_E) {
	this->the_text = text;
}

void Raw_Text_Block::set_text(QString text) {
	this->the_text = text;
}

QString Raw_Text_Block::text() {
	return this->the_text;
}

QString Raw_Text_Block::translate() {
	return this->the_text;
}
