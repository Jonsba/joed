#ifndef ABSTRACT_BLOCK_WIDGET_H
#define ABSTRACT_BLOCK_WIDGET_H

#include <QScrollArea>

class Abstract_Block;

class Focus_Manager;
class Block_Widget;

struct Widgets {
	QWidget* parent;
	QScrollArea* scroll_area;
	Focus_Manager* focus_manager;
	QWidget* next_widget_in_focus = nullptr;
};

class Abstract_Block_Widget : public QWidget {
 public:
	Abstract_Block_Widget(Widgets widgets, int type, int level);
	virtual void insert(Abstract_Block* first_sub_block, Block_Widget* sibling,
	                    bool insert_after) = 0;
	int level();

 private:
	int the_level;
};

#endif // ABSTRACT_BLOCK_WIDGET_H
