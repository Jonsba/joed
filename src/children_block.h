#ifndef CHILDREN_BLOCK_H
#define CHILDREN_BLOCK_H

#include "abstract_multi_block.h"

class Children_Block : public Abstract_Multi_Block {
 public:
	Children_Block(bool auto_built);
	void append_default_child();
	Abstract_Multi_Block* insert_default_child(Abstract_Block* first_sub_block,
	                                           Abstract_Block* sibling, bool insert_after);
};

#endif // CHILDREN_BLOCK_H
