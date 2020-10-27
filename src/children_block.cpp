#include "children_block.h"

Children_Block::Children_Block()
    : Abstract_Non_Layouted_Block(Children_Block_Id, Block_Type::Children_Block_E) {}

QString Children_Block::translate() {
	return Abstract_Non_Layouted_Block::translate();
}
