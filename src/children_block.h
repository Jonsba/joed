#ifndef CHILDREN_BLOCK_H
#define CHILDREN_BLOCK_H

#include "abstract_multi_block.h"

class Children_Block : public Abstract_Multi_Block {
 public:
	Children_Block(Abstract_Multi_Block* parent, bool auto_built);
};

#endif // CHILDREN_BLOCK_H
