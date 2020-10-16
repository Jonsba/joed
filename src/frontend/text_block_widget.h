#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include <QTextEdit>
#include <QWidget>

class Text_Block;
class Multi_Block_Widget;
class QVBoxLayout;

class Text_Block_Widget : public QTextEdit {
	Q_OBJECT
 public:
	explicit Text_Block_Widget(QVBoxLayout* widget_container, Text_Block* top_block);

 private:
	void text_changed();
	//
	Text_Block* block;
};

#endif // TEXT_WIDGET_H
