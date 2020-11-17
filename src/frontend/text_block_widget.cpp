#include "text_block_widget.h"
#include "color_scheme.h"

#include "src/joed.h"
#include "src/raw_text_block.h"
#include "src/text_block.h"

Text_Block_Widget::Text_Block_Widget(QWidget* parent, Text_Block* text_block, int level)
    : QTextEdit(parent) {
	this->text_block = text_block;
	this->color_scheme.reset(new Color_Scheme(level));
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setFrameStyle(QFrame::Box);
	this->setLineWidth(0);
	this->setPalette(this->color_scheme->palette());
	QFontMetrics metrics = this->fontMetrics();
	this->setMinimumHeight(this->fontMetrics().height());
	if (text_block->type().variant == Block_Variant::Title_E) {
		QFont font = this->font();
		font.setPointSize(16);
		this->setFont(font);
	}
	for (auto block : text_block->blocks()) {
		switch (block->type().base) {
		case Block_Base_Type::Raw_Text_Block_E:
			this->setPlainText(((Raw_Text_Block*)block)->text());
			break;
		default:
			error("Unimplemented!");
		}
	}
	QObject::connect(this, &Text_Block_Widget::textChanged, this,
	                 &Text_Block_Widget::on_text_changed);
}

void Text_Block_Widget::resize_to_fit_contents() {
	this->setFixedHeight(this->document()->size().toSize().height() + 3);
}

void Text_Block_Widget::on_text_changed() {
	// TODO deal with multiple subblocks in the textblock
	Raw_Text_Block* raw_text_block = (Raw_Text_Block*)this->text_block->blocks().first();
	raw_text_block->set_text(this->toPlainText());
	this->resize_to_fit_contents();
}

void Text_Block_Widget::resizeEvent(QResizeEvent* event) {
	QTextEdit::resizeEvent(event);
	this->resize_to_fit_contents();
}

Text_Block_Widget::~Text_Block_Widget() = default;
