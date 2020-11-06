#include "abstract_non_layouted_block.h"
#include "style.h"

Abstract_Non_Layouted_Block::Abstract_Non_Layouted_Block(QString identifier, Block_Type type)
    : Abstract_Multi_Block(identifier, type) {}

QString Abstract_Non_Layouted_Block::translate() {
	QStringList child_contents;
	for (Abstract_Block* child_block : this->the_blocks) {
		child_contents.append(child_block->translate());
	}
	return child_contents.join("\n\n");
}
