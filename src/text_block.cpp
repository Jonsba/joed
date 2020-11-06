#include "text_block.h"
#include "escaper.h"
#include "style.h"
#include "writer.h"

Text_Block::Text_Block(Style* style, Escaper* escaper)
    : Abstract_Non_Layouted_Block(style->name(), style->type()) {
	this->style = style;
	this->escaper = escaper;
}

QString Text_Block::translate() {
	QHash<QString, QString> global_dict = {};
	global_dict[Text_Content_Id] = this->escaper->escape(Abstract_Non_Layouted_Block::translate());
	return this->style->translate(global_dict);
}

void Text_Block::save(Writer* writer, int level) {
	this->Abstract_Block::save(writer, level);
	writer->write_pair(Joed::Keys[Style_E], this->style->name(), level + 1);
	this->Abstract_Multi_Block::save(writer, level + 1);
}
