#include "abstract_non_layouted_block.h"
#include "style.h"

Abstract_Non_Layouted_Block::Abstract_Non_Layouted_Block(QString Identifier, Block_Type Type)
    : Abstract_Multi_Block(Identifier, Type) {}

QString Abstract_Non_Layouted_Block::translate() {
	QStringList child_contents;
	for (Abstract_Block* child_block : this->the_blocks) {
		child_contents.append(child_block->translate());
	}
	return child_contents.join("\n\n");
}
