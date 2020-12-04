#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QScopedPointer>
#include <QTextEdit>

class Color_Scheme;
class Text_Block;

enum class Insertion_Action { Disabled, Object_Insertion, Parent_Insertion };

class Text_Edit : public QTextEdit {
 public:
	Text_Edit(QWidget* parent, Text_Block* text_block, int level, Insertion_Action insertion_action);
	~Text_Edit();

 private:
	void insert_sibling();
	void on_text_changed();
	void resize_to_fit_contents();
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	//
	Text_Block* text_block;
	Insertion_Action insertion_action;
};

#endif // TEXT_EDIT_H
