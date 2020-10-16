#include "text_block.h"
#include "joed.h"
#include "style.h"

Text_Block::Text_Block(Style* style) : Abstract_Block(style) {
	this->multiline = false;
	if (style->Get_Type() == Multiline_Text_Block_E) {
		this->multiline = true;
	}
}

void Text_Block::Set_Text_Contents(QString content) {
	this->text_content = content;
}

bool Text_Block::Is_Multiline() {
	return this->multiline;
}

QString Text_Block::Compile() {
	return this->style->Compile(Text_Value, this->text_content);
}
