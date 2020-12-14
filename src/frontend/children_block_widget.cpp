#include "children_block_widget.h"
#include "block_widget.h"
#include "focus_manager.h"

#include "src/children_block.h"
#include "src/joed.h"

#include <QApplication>
#include <QLayout>
#include <QSpacerItem>

Children_Block_Widget::Children_Block_Widget(Widgets widgets, Children_Block* children_block,
                                             int level)
    : Abstract_Block_Widget(widgets, CHILDREN_WIDGET, level) {
	widgets.parent = this;
	this->widgets = widgets;
	this->children_block = children_block;
	//
	this->container = new QVBoxLayout(this);
	this->container->setMargin(0);
	this->container->setSpacing(1);
	for (Abstract_Block* block = children_block->first_child(); block != nullptr;
	     block = block->next()) {
		Block_Widget* child_block = new Block_Widget(widgets, (Abstract_Multi_Block*)block, level);
		this->container->addWidget(child_block, 0);
	}
	// This prevents unwanted stretching of block widgets in case they can't fill the screen
	if (level == 1) {
		this->container->addItem(
		    new QSpacerItem(0, 1000000, QSizePolicy::Expanding, QSizePolicy::Expanding));
	}
}

void Children_Block_Widget::insert(Abstract_Block* first_sub_block, Block_Widget* sibling,
                                   bool insert_after) {
	this->widgets.next_widget_in_focus = sibling;
	int index = this->container->indexOf(sibling);
	if (insert_after) {
		this->widgets.next_widget_in_focus = this->widgets.focus_manager->next_widget_after(sibling);
		index += 1;
	}
	Abstract_Multi_Block* block =
	    this->children_block->insert_default_child(first_sub_block, sibling->block(), insert_after);
	QWidget* widget = new Block_Widget(this->widgets, block, this->level());
	this->container->insertWidget(index, widget);
	this->widgets.focus_manager->focus_neighboor(widget);
}

Children_Block_Widget::~Children_Block_Widget() = default;
