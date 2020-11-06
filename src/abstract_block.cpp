#include "abstract_block.h"
#include "writer.h"

Abstract_Block::Abstract_Block(QString identifier, Block_Type type)
    : Identifier(identifier), Type(type) {}

QString Abstract_Block::identifier() {
	return this->Identifier;
}

Block_Type Abstract_Block::type() {
	return this->Type;
}

void Abstract_Block::save(Writer* writer, int level) {
	writer->write_key(Joed::Keys[Block_E], level);
}
