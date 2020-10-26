#ifndef MULTI_BLOCK_WIDGET_H
#define MULTI_BLOCK_WIDGET_H

#include <QWidget>

class Abstract_Multi_Block;
class QVBoxLayout;

class Multi_Block_Widget : public QWidget {
 public:
	Multi_Block_Widget(QWidget* parent, Abstract_Multi_Block* multi_block);

 protected:
	Abstract_Multi_Block* multi_block;
	QVBoxLayout* block_widgets_container;
};

#endif // MULTI_BLOCK_WIDGET_H
