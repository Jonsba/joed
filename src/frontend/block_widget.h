#ifndef BLOCK_WIDGET_H
#define BLOCK_WIDGET_H

#include <QScopedPointer>
#include <QWidget>

class Abstract_Block;
class Abstract_Multi_Block;
class Children_Block_Widget;
class Color_Scheme;
class Text_Block;

class QVBoxLayout;

class Block_Widget : public QWidget {
 public:
	Block_Widget(QWidget* parent, Abstract_Multi_Block* block, int level, bool insertion_allowed);
	~Block_Widget();
	void insert();
	void insert(Abstract_Block* block);
	Abstract_Multi_Block* block();

 protected:
	static inline const int Horizontal_Spacing = 10;
	//
	Abstract_Multi_Block* the_block;
	int level;
};

#endif // BLOCK_WIDGET_H
