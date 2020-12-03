#include "text_edit.h"
#include "block_widget.h"
#include "children_block_widget.h"
#include "color_scheme.h"
#include "src/joed.h"
#include "src/raw_text_block.h"
#include "src/styles.h"
#include "src/text_block.h"

#include <QKeyEvent>

Text_Edit::Text_Edit(QWidget* parent, Text_Block* text_block, int level,
                     Insertion_Action insertion_action)
    : QTextEdit(parent) {
	this->text_block = text_block;
	this->insertion_action = insertion_action;
	Color_Scheme color_scheme(level);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setFrameStyle(QFrame::Box);
	this->setLineWidth(0);
	this->setPalette(color_scheme.palette());
	QFontMetrics metrics = this->fontMetrics();
	this->setMinimumHeight(this->fontMetrics().height());
	if (text_block->style()->variant == Style_Variant::Title) {
		QFont font = this->font();
		font.setPointSize(16);
		this->setFont(font);
	}
	for (Abstract_Block* block = text_block->first_child(); block != nullptr;
	     block = block->next()) {
		switch (block->style()->type) {
		case Style_Type::Raw_Text:
			this->setPlainText(((Raw_Text_Block*)block)->text());
			break;
		default:
			throw Exceptions::Not_Implemented();
		}
	}
	QObject::connect(this, &Text_Edit::textChanged, this, &Text_Edit::on_text_changed);
}

void Text_Edit::resize_to_fit_contents() {
	this->setFixedHeight(this->document()->size().toSize().height() + 3);
}

void Text_Edit::on_text_changed() {
	// TODO deal with multiple subblocks in the textblock
	Raw_Text_Block* raw_text_block = (Raw_Text_Block*)this->text_block->first_child();
	raw_text_block->set_text(this->toPlainText());
	this->resize_to_fit_contents();
}

void Text_Edit::resizeEvent(QResizeEvent* event) {
	QTextEdit::resizeEvent(event);
	this->resize_to_fit_contents();
}

void Text_Edit::keyPressEvent(QKeyEvent* event) {
	if (event->key() != Qt::Key_Return || event->modifiers().testFlag(Qt::ShiftModifier)) {
		QTextEdit::keyPressEvent(event);
		return;
	}
	auto parent = (Block_Widget*)this->parent();
	int cursor = this->textCursor().position();
	QString content = this->toPlainText();
	switch (this->insertion_action) {
	case Insertion_Action::Object_Insertion: {
		auto new_block =
		    (Text_Block*)this->text_block->insert_sibling(this->text_block->style(), false);
		auto raw_text_block = (Raw_Text_Block*)new_block->append_child(Styles::Raw_Text_Style);
		if (cursor > 0 || content.length() == 0) {
			raw_text_block->set_text(content.right(content.length() - cursor));
			parent->insert(new_block, false);
			this->setPlainText(content.left(cursor));
		} else {
			raw_text_block->set_text("");
			parent->insert(new_block, true);
		}
		break;
	}
	case Insertion_Action::Parent_Insertion:
		if (cursor == 0) {
			parent->insert(true);
		} else if (cursor == content.length()) {
			parent->insert(false);
		}
		break;
	case Insertion_Action::Disabled:
		break;
	}
}

Text_Edit::~Text_Edit() = default;
