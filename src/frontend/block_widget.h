#ifndef BLOCK_WIDGET_H
#define BLOCK_WIDGET_H

#include "abstract_block_widget.h"

class Abstract_Block;
class Abstract_Multi_Block;

class Children_Block_Widget;
class Focus_Manager;

class Block_Widget : public Abstract_Block_Widget {
 public:
	Block_Widget(Widgets widgets, Abstract_Multi_Block* block, int level);
	~Block_Widget();
	void insert(Abstract_Block* first_sub_block, bool insert_after);
	void insert(Abstract_Block* first_sub_block, Block_Widget* sibling, bool insert_after) override;
	Abstract_Multi_Block* block();

 protected:
	bool focusNextPrevChild(bool next) override;
	static inline const int Horizontal_Spacing = 10;
	//
	Widgets widgets;
	Children_Block_Widget* children_widget_block = nullptr;
	Abstract_Multi_Block* the_block;
};

#endif // BLOCK_WIDGET_H
