#include "abstract_non_layouted_block.h"
#include "style.h"

Abstract_Non_Layouted_Block::Abstract_Non_Layouted_Block(QString Identifier, Block_Type Type)
    : Abstract_Multi_Block(Identifier, Type) {}

QString Abstract_Non_Layouted_Block::to_backend_code() {
	QString child_contents = "";
	for (Abstract_Block* child_block : this->the_blocks) {
		child_contents += child_block->to_backend_code();
	}
	return child_contents;
}
