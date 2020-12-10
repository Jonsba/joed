#include "children_block_widget.h"
#include "focus_manager.h"

#include "src/children_block.h"
#include "src/joed.h"

#include <QApplication>
#include <QLayout>
#include <QSpacerItem>

Children_Block_Widget::Children_Block_Widget(Widgets widgets, Children_Block* children_block,
                                             int level)
    : QWidget(widgets.parent) {
	this->level = level;
	this->widgets = widgets;
	this->container = new QVBoxLayout(this);
	this->container->setMargin(0);
	this->container->setSpacing(1);
	widgets.parent = this;
	for (Abstract_Block* block = children_block->first_child(); block != nullptr;
	     block = block->next()) {
		Block_Widget* child_block =
		    new Block_Widget(widgets, (Abstract_Multi_Block*)block, level, true);
		this->container->addWidget(child_block, 0);
	}
	// This prevents unwanted stretching of block widgets in case they can't fill the screen
	if (level == 1) {
		this->container->addItem(
		    new QSpacerItem(0, 1000000, QSizePolicy::Expanding, QSizePolicy::Expanding));
	}
}

void Children_Block_Widget::insert(Abstract_Multi_Block* block, Block_Widget* sibling,
                                   bool insert_after) {
	this->widgets.next_widget_in_focus = sibling;
	int offset = 0;
	if (insert_after) {
		this->widgets.next_widget_in_focus = this->widgets.focus_manager->next_widget_after(sibling);
		offset = 1;
	}
	QWidget* widget = new Block_Widget(this->widgets, block, this->level, true);
	this->container->insertWidget(this->container->indexOf(sibling) + offset, widget);
	this->widgets.focus_manager->focus_neighboor(widget);
}

Children_Block_Widget::~Children_Block_Widget() = default;
