#ifndef BLOCK_WIDGET_H
#define BLOCK_WIDGET_H

#include "widgets.h"

#include <QWidget>

class Abstract_Block;
class Abstract_Multi_Block;
class Focus_Manager;

class Block_Widget : public QWidget {
 public:
	Block_Widget(Widgets widgets, Abstract_Multi_Block* block, int the_level,
	             bool is_insertion_allowed);
	~Block_Widget();
	void insert_same_style_sibling(bool insert_after);
	void insert_sibling(Abstract_Multi_Block* block, bool insert_after);
	Abstract_Multi_Block* block();
	int level();

 protected:
	bool focusNextPrevChild(bool next) override;
	static inline const int Horizontal_Spacing = 10;
	//
	Widgets widgets;
	Abstract_Multi_Block* the_block;
	int the_level;
};

#endif // BLOCK_WIDGET_H
