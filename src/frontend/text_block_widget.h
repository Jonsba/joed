#ifndef TEXT_BLOCK_WIDGET_H
#define TEXT_BLOCK_WIDGET_H

#include <QScopedPointer>
#include <QTextEdit>

class Color_Scheme;
class Text_Block;

class Text_Block_Widget : public QTextEdit {
 public:
	Text_Block_Widget(QWidget* parent, Text_Block* text_block, int level);
	~Text_Block_Widget();

 private:
	void on_text_changed();
	void resize_to_fit_contents();
	void resizeEvent(QResizeEvent* event);
	//
	Text_Block* text_block;
	QScopedPointer<Color_Scheme> color_scheme;
};

#endif // TEXT_BLOCK_WIDGET_H
