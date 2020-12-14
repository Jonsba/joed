#include "block_widget.h"
#include "children_block_widget.h"
#include "color_scheme.h"
#include "focus_manager.h"
#include "text_edit.h"

#include "src/abstract_multi_block.h"
#include "src/exceptions.h"
#include "src/style.h"

#include <QLayout>

Block_Widget::Block_Widget(Widgets widgets, Abstract_Multi_Block* block, int level)
    : Abstract_Block_Widget(widgets, BLOCK_WIDGET, level) {
	this->widgets = widgets;
	this->the_block = block;
	//
	Color_Scheme color_scheme(level);
	this->setPalette(color_scheme.palette(Widget_State::Highlighted));
	this->setAutoFillBackground(true);
	QHBoxLayout* top_container = new QHBoxLayout(this);
	top_container->setMargin(0);
	top_container->addItem(
	    new QSpacerItem(Horizontal_Spacing, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
	QVBoxLayout* blocks_container = new QVBoxLayout();
	blocks_container->setAlignment(Qt::AlignTop);
	blocks_container->setSpacing(1);
	blocks_container->setMargin(0);
	//
	widgets.parent = this;
	QWidget* sub_block_widget;
	if (block->style()->type == Style_Type::Text) {
		sub_block_widget = new Text_Edit(widgets, (Text_Block*)block, level);
		blocks_container->addWidget(sub_block_widget);
	} else {
		for (Abstract_Block* sub_block = block->first_child(); sub_block != nullptr;
		     sub_block = sub_block->next()) {
			switch (sub_block->style()->type) {
			case Style_Type::Children:
				this->children_widget_block =
				    new Children_Block_Widget(widgets, (Children_Block*)sub_block, level + 1);
				sub_block_widget = this->children_widget_block;
				break;
			case Style_Type::Layouted:
				sub_block_widget =
				    new Block_Widget(widgets, (Abstract_Multi_Block*)sub_block, level + 1);
				break;
			case Style_Type::Text: {
				sub_block_widget = new Text_Edit(widgets, (Text_Block*)sub_block, level);
				break;
			}
			default:
				throw Exceptions::Not_Implemented();
			}
			blocks_container->addWidget(sub_block_widget);
		}
	}
	top_container->addLayout(blocks_container);
	this->setLayout(top_container);
}

Abstract_Multi_Block* Block_Widget::block() {
	return this->the_block;
}

void Block_Widget::insert(Abstract_Block* first_sub_block, bool insert_after) {
	this->insert(first_sub_block, this, insert_after);
}

void Block_Widget::insert(Abstract_Block* first_sub_block, Block_Widget* sibling,
                          bool insert_after) {
	if (insert_after && this->children_widget_block != nullptr) {
		if (sibling == this) {
			sibling = (Block_Widget*)this->widgets.focus_manager->next_widget_after(
			    this->children_widget_block, BLOCK_WIDGET);
			insert_after = false;
		}
		this->children_widget_block->insert(first_sub_block, sibling, insert_after);
		return;
	}
	if (this->level() > 0) {
		((Abstract_Block_Widget*)this->parent())->insert(first_sub_block, this, insert_after);
	}
}

bool Block_Widget::focusNextPrevChild(bool next) {
	this->widgets.focus_manager->focus_neighboor(this->focusWidget(), next);
	return true;
}

Block_Widget::~Block_Widget() {
	this->widgets.focus_manager->remove(this);
}
