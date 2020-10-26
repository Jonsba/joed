#include "children_block.h"

Children_Block::Children_Block()
    : Abstract_Non_Layouted_Block(Children_Block_Id, Children_Block_E) {}

QString Children_Block::to_backend_code() {
	return Abstract_Non_Layouted_Block::to_backend_code();
}
