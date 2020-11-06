#ifndef CHILDREN_BLOCK_H
#define CHILDREN_BLOCK_H

#include "abstract_non_layouted_block.h"

class Children_Block : public Abstract_Non_Layouted_Block {
 public:
	Children_Block();
	QString translate() override;
	void save(Writer* writer, int level) override;
};

#endif // CHILDREN_BLOCK_H
