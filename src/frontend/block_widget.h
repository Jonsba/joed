#ifndef BLOCK_WIDGET_H
#define BLOCK_WIDGET_H

#include <QWidget>

class Abstract_Block;
class Abstract_Multi_Block;

class QScrollArea;

class Block_Widget : public QWidget {
 public:
	Block_Widget(QWidget* parent, QScrollArea* scroll_area, Abstract_Multi_Block* block, int level,
	             bool is_insertion_allowed);
	~Block_Widget();
	void insert(bool insertion_is_before);
	void insert(Abstract_Block* block, bool insertion_is_before);
	Abstract_Multi_Block* block();

 protected:
	static inline const int Horizontal_Spacing = 10;
	//
	Abstract_Multi_Block* the_block;
	int level;
};

#endif // BLOCK_WIDGET_H
