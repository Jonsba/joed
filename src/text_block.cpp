#include "text_block.h"
#include "style.h"

Text_Block::Text_Block(Style* style)
    : Abstract_Non_Layouted_Block(style->name(), style->type()), I_Styled_Block(style) {}

QString Text_Block::translate() {
	QHash<QString, QString> global_dict;
	global_dict[Text_Content_Id] = Abstract_Non_Layouted_Block::translate();
	return this->the_style->translate(global_dict);
}
