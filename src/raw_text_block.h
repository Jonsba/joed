#ifndef RAW_TEXT_BLOCK_H
#define RAW_TEXT_BLOCK_H

#include "abstract_block.h"

class Escaper;

class Raw_Text_Block : public Abstract_Block {
 public:
	Raw_Text_Block(Abstract_Multi_Block* parent);
	void set_text(QString text);
	void add_quoted_text(QString quoted_text);
	QString text();
	QString translate(Escaper* escaper) override;
	void save(Writer* writer, int level) override;

 private:
	QString the_text;
};

#endif // RAW_TEXT_BLOCK_H
