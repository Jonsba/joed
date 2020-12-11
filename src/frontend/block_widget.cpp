#include "block_widget.h"
#include "children_block_widget.h"
#include "color_scheme.h"
#include "focus_manager.h"
#include "text_edit.h"

#include "src/abstract_multi_block.h"
#include "src/exceptions.h"
#include "src/style.h"

#include <QLayout>

Block_Widget::Block_Widget(Widgets widgets, Abstract_Multi_Block* block, int level,
                           bool is_insertion_allowed)
    : QWidget(widgets.parent) {
	this->widgets = widgets;
	this->the_block = block;
	this->the_level = level;
	widgets.focus_manager->insert(this, widgets.next_widget_in_focus, BLOCK_WIDGET);
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
	Insertion_Action allowed_insert = Insertion_Action::Disabled;
	if (block->style()->type == Style_Type::Text) {
		if (is_insertion_allowed) {
			allowed_insert = Insertion_Action::Object_Insertion;
		}
		sub_block_widget = new Text_Edit(widgets, (Text_Block*)block, level, allowed_insert);
		blocks_container->addWidget(sub_block_widget);
	} else {
		for (Abstract_Block* sub_block = block->first_child(); sub_block != nullptr;
		     sub_block = sub_block->next()) {
			switch (sub_block->style()->type) {
			case Style_Type::Children:
				sub_block_widget =
				    new Children_Block_Widget(widgets, (Children_Block*)sub_block, level + 1);

				break;
			case Style_Type::Layouted:
				sub_block_widget = new Block_Widget(widgets, (Abstract_Multi_Block*)sub_block,
				                                    level + 1, is_insertion_allowed);
				break;
			case Style_Type::Text: {
				if (is_insertion_allowed) {
					allowed_insert = Insertion_Action::Parent_Insertion;
				}
				sub_block_widget =
				    new Text_Edit(widgets, (Text_Block*)sub_block, level, allowed_insert);
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

int Block_Widget::level() {
	return this->the_level;
}

Abstract_Multi_Block* Block_Widget::block() {
	return this->the_block;
}

void Block_Widget::insert_same_style_sibling(bool insert_after) {
	auto new_sibling = (Abstract_Multi_Block*)this->block()->insert_sibling(this->block()->style(),
	                                                                        insert_after, true);
	this->insert_sibling(new_sibling, insert_after);
}

void Block_Widget::insert_sibling(Abstract_Multi_Block* block, bool insert_after) {
	auto parent = (Children_Block_Widget*)this->parent();
	parent->insert(block, this, insert_after);
}

bool Block_Widget::focusNextPrevChild(bool next) {
	this->widgets.focus_manager->focus_neighboor(this->focusWidget(), next);
	return true;
}

Block_Widget::~Block_Widget() {
	this->widgets.focus_manager->remove(this);
}
