#ifndef CHILDREN_WIDGET_BLOCK_H
#define CHILDREN_WIDGET_BLOCK_H

#include <QScopedPointer>
#include <QWidget>

class Color_Scheme;
class Children_Block;
class Multi_Block_Widget;

class Children_Widget_Block : public QWidget {
 public:
	Children_Widget_Block(QWidget* parent, Children_Block* children_block, int level);
	~Children_Widget_Block();
	//
	static inline const int Horizontal_Spacing = 10;

 private:
	Multi_Block_Widget* multi_block_widget;
	QScopedPointer<Color_Scheme> color_scheme;
};

#endif // CHILDREN_WIDGET_BLOCK_H
