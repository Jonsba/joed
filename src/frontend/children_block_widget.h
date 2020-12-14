#ifndef CHILDREN_BLOCK_WIDGET_H
#define CHILDREN_BLOCK_WIDGET_H

#include "abstract_block_widget.h"

class Abstract_Multi_Block;
class Block_Widget;
class Children_Block;

class QVBoxLayout;

class Children_Block_Widget : public Abstract_Block_Widget {
 public:
	Children_Block_Widget(Widgets widgets, Children_Block* children_block, int the_level);
	~Children_Block_Widget();
	void insert(Abstract_Block* first_sub_block, Block_Widget* sibling, bool insert_after) override;

 private:
	QVBoxLayout* container;
	Widgets widgets;
	Children_Block* children_block;
};

#endif // CHILDREN_BLOCK_WIDGET_H
