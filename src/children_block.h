#ifndef CHILDREN_BLOCK_H
#define CHILDREN_BLOCK_H

#include "abstract_non_layouted_block.h"

class Children_Block : public Abstract_Non_Layouted_Block {
 public:
	Children_Block();
	void save(Writer* writer, int level) override;
	QString translate() override;
	// Undoes method shadowing
	using Abstract_Multi_Block::create_block;

 private:
	Abstract_Block* create_block(Block_Type type, Style* style, Escaper* escaper) override;
};

#endif // CHILDREN_BLOCK_H
