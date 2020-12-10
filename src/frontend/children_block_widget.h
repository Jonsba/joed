#ifndef CHILDREN_BLOCK_WIDGET_H
#define CHILDREN_BLOCK_WIDGET_H

#include "block_widget.h"

class Abstract_Multi_Block;
class Block_Widget;
class Children_Block;

class QVBoxLayout;

class Children_Block_Widget : public QWidget {
 public:
	Children_Block_Widget(Widgets widgets, Children_Block* children_block, int level);
	~Children_Block_Widget();
	void insert(Abstract_Multi_Block* block, Block_Widget* sibling, bool insert_after);

 private:
	QVBoxLayout* container;
	int level;
	Widgets widgets;
};

#endif // CHILDREN_BLOCK_WIDGET_H
