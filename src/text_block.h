#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "abstract_multi_block.h"

class Escaper;
class Raw_Text_Block;

class Text_Block : public Abstract_Multi_Block {
 public:
	Text_Block(Style* style, Abstract_Multi_Block* parent, bool auto_built);
	Abstract_Block* create_block(Style* style) override;
	QString translate(Escaper* escaper) override;
	void save(Writer* writer, int level) override;

 private:
	//
	Raw_Text_Block* current_sub_block;
};

#endif // TEXT_BLOCK_H
