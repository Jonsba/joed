#include "text_block_widget.h"
#include "src/text_block.h"

#include <QLayout>

Text_Block_Widget::Text_Block_Widget(QVBoxLayout* widget_container, Text_Block* block) {
	this->block = block;
	if (! block->Is_Multiline()) {
		this->document()->setMaximumBlockCount(1);
	}
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	widget_container->addWidget(this);
	QObject::connect(this, &QTextEdit::textChanged, this, &Text_Block_Widget::Text_Changed);
}
void Text_Block_Widget::Text_Changed() {
	this->block->Set_Text_Contents(this->toPlainText());
	// Resize the block to fit its text
	QSize size = this->document()->size().toSize();
	this->setFixedHeight(size.height() + 3);
}
