#include "multi_block_widget.h"
#include "src/abstract_block.h"
#include "src/joed.h"
#include "src/layout_entry.h"
#include "src/multi_block.h"
#include "src/styles.h"
#include "src/text_block.h"
#include "text_block_widget.h"
#include <QLayout>

Multi_Block_Widget::Multi_Block_Widget(QVBoxLayout* widget_container, Multi_Block* top_block) {
	this->top_block = top_block;
	widget_container->addWidget(this);
	this->child_widget_container = new QVBoxLayout(); // (parent) ????
	this->child_widget_container->setAlignment(Qt::AlignTop);
	widget_container->addLayout(child_widget_container);
	this->create_layout();
}

void Multi_Block_Widget::create_layout() {
	QWidget* new_widget;
	for (Layout_Entry* layout_entry : top_block->style()->layout_entries()) {
		Style* style;
		if (layout_entry->is_children_block()) {
			style = this->top_block->style()->default_child_style();
		} else {
			style = layout_entry->style();
		}
		Abstract_Block* child_block;
		if (style->type() == Multi_Block_E) {
			child_block = new Multi_Block(style);
			new_widget =
			    new Multi_Block_Widget(this->child_widget_container, (Multi_Block*)child_block);
		} else {
			child_block = new Text_Block(style);
			new_widget = new Text_Block_Widget(this->child_widget_container, (Text_Block*)child_block);
		}
		this->top_block->add_block(child_block);
		// TODO : check layout_entry.Is_A_Child()
	}
}
