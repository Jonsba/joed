#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_non_layouted_block.h"

class Style;
class Escaper;

class Text_Block : public Abstract_Non_Layouted_Block {
 public:
	Text_Block(Style* style, Escaper* escaper);
	Abstract_Block* create_block(Block_Type type) {
		return Abstract_Multi_Block::create_block(type);
	}
	QString translate() override;
	void save(Writer* writer, int level) override;

 private:
	Abstract_Block* create_block(Block_Type type, Style* style, Escaper* escaper) override;
	//
	Style* style;
	Escaper* escaper;
};

#endif // TEXT_BLOCK_H
