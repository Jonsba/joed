#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_non_layouted_block.h"

class Style;
class Escaper;
class Raw_Text_Block;

class Text_Block : public Abstract_Non_Layouted_Block {
 public:
	Text_Block(Style* style, Escaper* escaper, bool auto_built);
	QString translate() override;
	void save(Writer* writer, int level) override;

 private:
	Abstract_Block* create_block(Block_Type type) {
		return Abstract_Multi_Block::create_block(type);
	}
	Abstract_Block* create_block(Block_Type type, Style* style, Escaper* escaper) override;
	//
	Style* style;
	Escaper* escaper;
	Raw_Text_Block* current_sub_block;
};

#endif // TEXT_BLOCK_H
