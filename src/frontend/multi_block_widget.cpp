#include "multi_block_widget.h"
#include "children_widget_block.h"
#include "color_scheme.h"
#include "text_block_widget.h"

#include "src/joed.h"
#include "src/styles.h"
#include "src/text_block.h"

#include <QLayout>

Multi_Block_Widget::Multi_Block_Widget(QWidget* parent, Abstract_Multi_Block* multi_block,
                                       int level)
    : QWidget(parent) {

	this->multi_block = multi_block;
	this->color_scheme.reset(new Color_Scheme(level));
	this->setPalette(this->color_scheme->palette(Widget_State::Inactive_E));
	this->setAutoFillBackground(true);
	this->block_widgets_container = new QVBoxLayout();
	this->block_widgets_container->setAlignment(Qt::AlignTop);
	this->block_widgets_container->setSpacing(2);
	this->block_widgets_container->setMargin(0);
	this->setLayout(this->block_widgets_container);
	//
	for (Abstract_Block* block = multi_block->first_child(); block != nullptr;
	     block = block->next()) {
		QWidget* block_widget;
		switch (block->style()->type) {
		case Style_Type::Children_E:
			block_widget = new Children_Widget_Block(this, (Children_Block*)block, level);
			break;
		case Style_Type::Layouted_E:
			block_widget = new Multi_Block_Widget(this, (Abstract_Multi_Block*)block, level);
			break;
		case Style_Type::Text_E:
			block_widget = new Text_Block_Widget(this, (Text_Block*)block, level);
			break;
		default:
			throw Exceptions::Not_Implemented();
		}
		this->block_widgets_container->addWidget(block_widget);
	}
}

Multi_Block_Widget::~Multi_Block_Widget() = default;
