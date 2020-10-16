#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_block.h"

class Text_Block : public Abstract_Block {
 public:
	Text_Block(Style* style);
	void set_text_contents(QString content);
	bool is_multiline();
	QString compile();

 private:
	QString text_content;
	bool multiline;
};

#endif // TEXT_BLOCK_H
