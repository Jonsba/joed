#include "multi_block_widget.h"
#include "children_widget_block.h"
#include "src/abstract_block.h"
#include "src/abstract_multi_block.h"
#include "src/joed.h"
#include "src/layout_block.h"
#include "src/layout_entry.h"
#include "src/raw_text_block.h"
#include "src/style.h"
#include "src/styles.h"
#include "src/text_block.h"
#include "text_block_widget.h"
#include <QLayout>
#include <QTextEdit>

Multi_Block_Widget::Multi_Block_Widget(QWidget* parent, Abstract_Multi_Block* multi_block)
    : QWidget(parent) {
	this->multi_block = multi_block;
	this->block_widgets_container = new QVBoxLayout();
	this->block_widgets_container->setAlignment(Qt::AlignTop);
	this->setLayout(this->block_widgets_container);
	//
	for (auto block : multi_block->blocks()) {
		QWidget* block_widget;
		switch (block->type()) {
		case Children_Block_E:
			block_widget = new Children_Widget_Block(this, (Children_Block*)block);
			break;
		case Layout_Block_E:
			block_widget = new Multi_Block_Widget(this, (Layout_Block*)block);
			break;
		case Text_Block_E:
			block_widget = new Text_Block_Widget(this, (Text_Block*)block);
			break;
		default:
			error("Unimplemented!");
		}
		this->block_widgets_container->addWidget(block_widget);
	}
}
