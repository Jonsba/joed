#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_block.h"

class Text_Block : public Abstract_Block {
 public:
	Text_Block(Style* style);
	void Set_Text_Contents(QString content);
	bool Is_Multiline();
	QString Compile();

 private:
	QString text_content;
	bool multiline;
};

#endif // TEXT_BLOCK_H
