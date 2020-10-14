#ifndef BLOCK_WIDGET_H
#define BLOCK_WIDGET_H

#include <QWidget>

class Multi_Block;
class QVBoxLayout;

class Multi_Block_Widget : public QWidget {
	Q_OBJECT
 public:
	explicit Multi_Block_Widget(QVBoxLayout* widget_container, Multi_Block* top_block);

 private:
	void Create_Layout();
	//
	Multi_Block* top_block;
	QVBoxLayout* child_widget_container;

 signals:
};

#endif // BLOCK_WIDGET_H
