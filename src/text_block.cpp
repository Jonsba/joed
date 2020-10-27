#include "text_block.h"
#include "style.h"

Text_Block::Text_Block(Style* style)
    : Abstract_Non_Layouted_Block(style->name(), style->type()), I_Styled_Block(style) {}

QString Text_Block::to_backend_code() {
	QHash<QString, QString> global_dict;
	global_dict[Text_Content_Id] = Abstract_Non_Layouted_Block::to_backend_code();
	return this->the_style->compile(global_dict);
}
