#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_non_layouted_block.h"

class Style;
class Escaper;

class Text_Block : public Abstract_Non_Layouted_Block {
 public:
	Text_Block(Style* style, Escaper* escaper);
	QString translate() override;
	void save(Writer* writer, int level) override;

 private:
	Style* style;
	Escaper* escaper;
};

#endif // TEXT_BLOCK_H
