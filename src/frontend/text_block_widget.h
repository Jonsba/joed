#ifndef TEXT_BLOCK_WIDGET_H
#define TEXT_BLOCK_WIDGET_H

#include <QTextEdit>

class Text_Block;

class Text_Block_Widget : public QTextEdit {
 public:
	Text_Block_Widget(QWidget* parent, Text_Block* text_block);

 private:
	void text_changed();
	//
	Text_Block* text_block;
};

#endif // TEXT_BLOCK_WIDGET_H
