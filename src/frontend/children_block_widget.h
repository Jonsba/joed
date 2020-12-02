#ifndef CHILDREN_BLOCK_WIDGET_H
#define CHILDREN_BLOCK_WIDGET_H

#include <QScopedPointer>
#include <QWidget>

class Abstract_Block;
class Abstract_Multi_Block;
class Color_Scheme;
class Children_Block;
class Block_Widget;

class QVBoxLayout;

class Children_Block_Widget : public QWidget {
 public:
	Children_Block_Widget(QWidget* parent, Children_Block* children_block, int level);
	~Children_Block_Widget();
 public slots:
	void insert(Abstract_Multi_Block* block, Block_Widget* after);

 private:
	QVBoxLayout* container;
	int level;
};

#endif // CHILDREN_BLOCK_WIDGET_H
