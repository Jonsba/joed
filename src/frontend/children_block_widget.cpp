#include "children_block_widget.h"
#include "block_widget.h"

#include "color_scheme.h"
#include "src/children_block.h"
#include "src/joed.h"
#include "text_edit.h"

#include <QLayout>
#include <QSpacerItem>

Children_Block_Widget::Children_Block_Widget(QWidget* parent, Children_Block* children_block,
                                             int level)
    : QWidget(parent) {
	this->level = level;
	this->container = new QVBoxLayout(this);
	this->container->setMargin(0);
	this->container->setSpacing(2); //
	for (Abstract_Block* block = children_block->first_child(); block != nullptr;
	     block = block->next()) {
		this->container->addWidget(
		    new Block_Widget(this, (Abstract_Multi_Block*)block, level + 1, true));
	}
}

void Children_Block_Widget::insert(Abstract_Multi_Block* block, Block_Widget* after) {
	Block_Widget* block_widget = new Block_Widget(this, block, this->level + 1, true);
	this->container->insertWidget(this->container->indexOf(after) + 1, block_widget);
}

Children_Block_Widget::~Children_Block_Widget() = default;
