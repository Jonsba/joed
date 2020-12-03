#include "children_block_widget.h"
#include "block_widget.h"

#include "src/children_block.h"

#include <QApplication>
#include <QLayout>
#include <QScrollArea>
#include <QSpacerItem>

Children_Block_Widget::Children_Block_Widget(QWidget* parent, QScrollArea* scroll_area,
                                             Children_Block* children_block, int level)
    : QWidget(parent) {
	this->level = level;
	this->scroll_area = scroll_area;
	this->container = new QVBoxLayout(this);
	this->container->setMargin(0);
	this->container->setSpacing(1);
	for (Abstract_Block* block = children_block->first_child(); block != nullptr;
	     block = block->next()) {
		this->container->addWidget(
		    new Block_Widget(this, scroll_area, (Abstract_Multi_Block*)block, level + 1, true), 0);
	}
	// This prevents unwanted stretching of block widgets in case they can't fill the screen
	if (level == 0) {
		this->container->addItem(
		    new QSpacerItem(0, 1000000, QSizePolicy::Expanding, QSizePolicy::Expanding));
	}
}

void Children_Block_Widget::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	this->scroll_area->ensureWidgetVisible(qApp->focusWidget());
}

void Children_Block_Widget::insert(Abstract_Multi_Block* block, Block_Widget* after) {
	this->container->insertWidget(
	    this->container->indexOf(after) + 1,
	    new Block_Widget(this, this->scroll_area, block, this->level + 1, true));
}

Children_Block_Widget::~Children_Block_Widget() = default;
