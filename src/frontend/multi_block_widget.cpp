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
	Color_Scheme color_scheme(level);
	this->setPalette(color_scheme.palette(Widget_State::Highlighted_E));
	this->setAutoFillBackground(true);

	QHBoxLayout* top_container = new QHBoxLayout(this);
	top_container->setMargin(0);
	top_container->addItem(
	    new QSpacerItem(Horizontal_Spacing, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
	QVBoxLayout* blocks_container = new QVBoxLayout();
	blocks_container->setAlignment(Qt::AlignTop);
	blocks_container->setSpacing(2);
	blocks_container->setMargin(0);
	if (multi_block->style()->type == Style_Type::Text_E) {
		blocks_container->addWidget(new Text_Block_Widget(this, (Text_Block*)multi_block, level));
	} else {
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
			blocks_container->addWidget(block_widget);
		}
	}
	top_container->addLayout(blocks_container);
	this->setLayout(top_container);
}

Multi_Block_Widget::~Multi_Block_Widget() = default;
