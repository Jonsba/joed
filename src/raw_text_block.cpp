#include "raw_text_block.h"
#include "writer.h"

Raw_Text_Block::Raw_Text_Block()
    : Abstract_Block(Raw_Text_Block_Id, Block_Type::Raw_Text_Block_E) {}

void Raw_Text_Block::set_text(QString text) {
	this->the_text = text;
}

QString Raw_Text_Block::text() {
	return this->the_text;
}

QString Raw_Text_Block::translate() {
	return this->the_text;
}

void Raw_Text_Block::save(Writer* writer, int level) {
	writer->write_end_key(Joed::Keys[Text_E], level);
	writer->write_value('"' + this->the_text + '"', level + 1);
}
