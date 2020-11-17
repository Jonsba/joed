#ifndef MULTI_BLOCK_WIDGET_H
#define MULTI_BLOCK_WIDGET_H

#include <QScopedPointer>
#include <QWidget>

class Abstract_Multi_Block;
class Color_Scheme;

class QVBoxLayout;

class Multi_Block_Widget : public QWidget {
 public:
	Multi_Block_Widget(QWidget* parent, Abstract_Multi_Block* multi_block, int level);
	~Multi_Block_Widget();

 protected:
	Abstract_Multi_Block* multi_block;
	QVBoxLayout* block_widgets_container;
	QScopedPointer<Color_Scheme> color_scheme;
};

#endif // MULTI_BLOCK_WIDGET_H
