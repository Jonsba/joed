#ifndef CHILDREN_BLOCK_H
#define CHILDREN_BLOCK_H

#include "abstract_multi_block.h"

class Children_Block : public Abstract_Multi_Block {
 public:
	Children_Block(bool auto_built);
	Abstract_Block* create_block(Style* style) override;
};

#endif // CHILDREN_BLOCK_H
