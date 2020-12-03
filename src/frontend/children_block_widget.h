#ifndef CHILDREN_BLOCK_WIDGET_H
#define CHILDREN_BLOCK_WIDGET_H

#include <QScopedPointer>
#include <QWidget>

class Abstract_Multi_Block;
class Children_Block;
class Block_Widget;

class QVBoxLayout;
class QScrollArea;

class Children_Block_Widget : public QWidget {
 public:
	Children_Block_Widget(QWidget* parent, QScrollArea* scroll_area, Children_Block* children_block,
	                      int level);
	~Children_Block_Widget();
	void insert(Abstract_Multi_Block* block, Block_Widget* sibling, bool insertion_is_before);

 private:
	void resizeEvent(QResizeEvent* event) override;
	QVBoxLayout* container;
	int level;
	QScrollArea* scroll_area;
};

#endif // CHILDREN_BLOCK_WIDGET_H
