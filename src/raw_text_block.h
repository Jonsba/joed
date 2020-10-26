#ifndef RAW_TEXT_BLOCK_H
#define RAW_TEXT_BLOCK_H

#include "abstract_block.h"

class Raw_Text_Block : public Abstract_Block {
 public:
	Raw_Text_Block(QString text = "");
	void set_text(QString text);
	QString text();
	QString to_backend_code();

 private:
	QString the_text;
};

#endif // RAW_TEXT_BLOCK_H
