#include "text_edit.h"
#include "block_widget.h"
#include "color_scheme.h"
#include "focus_manager.h"

#include "src/joed.h"
#include "src/raw_text_block.h"
#include "src/style_properties.h"
#include "src/styles.h"
#include "src/text_block.h"

#include <QKeyEvent>
#include <QScrollArea>

Text_Edit::Text_Edit(Widgets widgets, Text_Block* text_block, int parent_level,
                     Insertion_Action insertion_action)
    : QTextEdit(widgets.parent) {
	this->the_level = parent_level + 1;
	this->scroll_area = widgets.scroll_area;
	widgets.focus_manager->insert(this, widgets.next_widget_in_focus, TEXT_EDIT);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->text_block = text_block;
	this->insertion_action = insertion_action;
	this->setTabChangesFocus(true);
	Color_Scheme color_scheme(parent_level);
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
	this->setPlaceholderText("Add a " + text_block->style()->properties->caption());
}

int Text_Edit::level() {
	return this->the_level;
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
	this->scroll_area->ensureWidgetVisible(this);
}

void Text_Edit::focusInEvent(QFocusEvent* event) {
	QTextEdit::focusInEvent(event);
	this->scroll_area->ensureWidgetVisible(this);
}

void Text_Edit::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Return: {
		// Insertion of a line break inside a paragraph?
		if (event->modifiers().testFlag(Qt::ShiftModifier)) {
			break;
		}
		this->insert_sibling();
		return;
	}
	default:
		break;
	}
	QTextEdit::keyPressEvent(event);
}

void Text_Edit::insert_sibling() {
	auto parent = (Block_Widget*)this->parent();
	int cursor = this->textCursor().position();
	QString content = this->toPlainText();
	switch (this->insertion_action) {
	case Insertion_Action::Object_Insertion: {
		bool insert_after = false;
		if (cursor > 0 || content.length() == 0) {
			insert_after = true;
		}
		auto new_sibling = (Text_Block*)this->text_block->insert_sibling(this->text_block->style(),
		                                                                 insert_after, false);
		auto raw_text_block = (Raw_Text_Block*)new_sibling->append_child(Styles::Raw_Text_Style);
		if (insert_after) {
			raw_text_block->set_text(content.right(content.length() - cursor));
			this->setPlainText(content.left(cursor));
		} else {
			raw_text_block->set_text("");
		}
		parent->insert_sibling(new_sibling, insert_after);
		break;
	}
	case Insertion_Action::Parent_Insertion:
		if (cursor == 0) {
			parent->insert_same_style_sibling(false);
		} else if (cursor == content.length()) {
			parent->insert_same_style_sibling(true);
		}
		break;
	case Insertion_Action::Disabled:
		break;
	}
}

Text_Edit::~Text_Edit() = default;
