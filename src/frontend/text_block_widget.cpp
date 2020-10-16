#include "text_block_widget.h"
#include "src/text_block.h"

#include <QLayout>

Text_Block_Widget::Text_Block_Widget(QVBoxLayout* widget_container, Text_Block* block) {
	this->block = block;
	if (! block->is_multiline()) {
		this->document()->setMaximumBlockCount(1);
	}
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	widget_container->addWidget(this);
	QObject::connect(this, &QTextEdit::textChanged, this, &Text_Block_Widget::text_changed);
}
void Text_Block_Widget::text_changed() {
	this->block->set_text_contents(this->toPlainText());
	// Resize the block to fit its text
	QSize size = this->document()->size().toSize();
	this->setFixedHeight(size.height() + 3);
}
