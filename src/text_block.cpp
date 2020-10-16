#include "text_block.h"
#include "joed.h"
#include "style.h"

Text_Block::Text_Block(Style* style) : Abstract_Block(style) {
	this->multiline = false;
	if (style->type() == Multiline_Text_Block_E) {
		this->multiline = true;
	}
}

void Text_Block::set_text_contents(QString content) {
	this->text_content = content;
}

bool Text_Block::is_multiline() {
	return this->multiline;
}

QString Text_Block::compile() {
	return this->the_style->compile(Text_Value, this->text_content);
}
