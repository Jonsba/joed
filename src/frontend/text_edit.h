#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QScopedPointer>
#include <QTextEdit>

class Color_Scheme;
class Text_Block;

enum class Insertion_Type { Denied_E, Text_Block_Insertion_E, Layout_Block_Insertion_E };

class Text_Edit : public QTextEdit {
 public:
	Text_Edit(QWidget* parent, Text_Block* text_block, int level, Insertion_Type allowed_insert);
	~Text_Edit();

 private:
	void on_text_changed();
	void resize_to_fit_contents();
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	//
	Text_Block* text_block;
	Insertion_Type allowed_insert;
};

#endif // TEXT_EDIT_H
