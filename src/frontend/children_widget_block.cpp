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
	this->color_scheme.reset(new Color_Scheme(level));
	this->setPalette(this->color_scheme->palette());
	this->setAutoFillBackground(true);

	QHBoxLayout* top_container = new QHBoxLayout();
	top_container->setMargin(0);
	top_container->addItem(
	    new QSpacerItem(Horizontal_Spacing, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
	this->multi_block_widget = new Multi_Block_Widget(this, children_block, level + 1);
	top_container->addWidget(this->multi_block_widget);
	this->setLayout(top_container);
}

Children_Widget_Block::~Children_Widget_Block() = default;
