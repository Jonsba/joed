#include "children_widget_block.h"
#include "color_scheme.h"
#include "multi_block_widget.h"

#include "src/children_block.h"
#include "src/joed.h"
#include <QLayout>
#include <QSpacerItem>

Children_Widget_Block::Children_Widget_Block(QWidget* parent, Children_Block* children_block,
                                             int level)
    : QWidget(parent) {
	QVBoxLayout* container = new QVBoxLayout(this);
	container->setMargin(0);
	container->setSpacing(2); //
	for (Abstract_Block* block = children_block->first_child(); block != nullptr;
	     block = block->next()) {
		container->addWidget(new Multi_Block_Widget(this, (Abstract_Multi_Block*)block, level + 1));
	}
}

Children_Widget_Block::~Children_Widget_Block() = default;
