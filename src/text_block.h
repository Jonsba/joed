#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_block.h"

class Text_Block : public Abstract_Block {
 public:
	Text_Block(Style* style);
	void Set_Text_Contents(QString content);
	QString Text_Contents();
	bool Is_Multiline();
	QString Backend_Contents();

 private:
	QString text_content;
	bool multiline;
};

#endif // TEXT_BLOCK_H
