#include "text_block_widget.h"
#include "src/joed.h"
#include "src/raw_text_block.h"
#include "src/text_block.h"

#include <QAbstractTextDocumentLayout>
#include <QLayout>

Text_Block_Widget::Text_Block_Widget(QWidget* parent, Text_Block* text_block) : QTextEdit(parent) {
	this->text_block = text_block;
	this->document()->setMaximumBlockCount(1);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QObject::connect(this, &QTextEdit::textChanged, this, &Text_Block_Widget::text_changed);

	QFontMetrics metrics = this->fontMetrics();
	this->setMinimumHeight(this->fontMetrics().height());
	//
	for (auto block : text_block->blocks()) {
		switch (block->type()) {
		case Block_Type::Raw_Text_Block_E:
			this->setPlainText(((Raw_Text_Block*)block)->text());
			break;
		default:
			error("Unimplemented!");
		}
	}
}

void Text_Block_Widget::text_changed() {
	// TODO deal with multiple subblocks in the textblock
	Raw_Text_Block* raw_text_block = (Raw_Text_Block*)this->text_block->blocks().first();
	raw_text_block->set_text(this->toPlainText());
	// Resize the block to fit its text
	int size = qMax(this->document()->size().toSize().height(), this->fontMetrics().height() + 8);
	this->setFixedHeight(size + 3);
}
