#include "children_widget_block.h"
#include "multi_block_widget.h"
#include "src/children_block.h"
#include "src/joed.h"
#include "text_block_widget.h"
#include <QLayout>
#include <QSpacerItem>

Children_Widget_Block::Children_Widget_Block(QWidget* parent, Children_Block* children_block)
    : QWidget(parent) {
	QHBoxLayout* top_container = new QHBoxLayout();
	top_container->addItem(
	    new QSpacerItem(Horizontal_Spacing, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
	this->multi_block_widget = new Multi_Block_Widget(this, children_block);
	top_container->addWidget(this->multi_block_widget);
	this->setLayout(top_container);
}
