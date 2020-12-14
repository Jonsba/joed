#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include "abstract_block_widget.h"

#include <QScopedPointer>
#include <QTextEdit>

class Color_Scheme;
class Text_Block;

class QScrollArea;

class Text_Edit : public QTextEdit {
 public:
	Text_Edit(Widgets widgets, Text_Block* text_block, int parent_level);
	~Text_Edit();
	int level();

 private:
	void insert();
	void on_text_changed();
	void resize_to_fit_contents();
	void resizeEvent(QResizeEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	//
	Widgets widgets;
	int the_level;
	Text_Block* text_block;
};

#endif // TEXT_EDIT_H
