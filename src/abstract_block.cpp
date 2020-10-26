#include "abstract_block.h"
#include "joed.h"

Abstract_Block::Abstract_Block(QString Identifier, Block_Type Type)
    : Identifier(Identifier), Type(Type) {}

QString Abstract_Block::identifier() {
	return this->Identifier;
}

Block_Type Abstract_Block::type() {
	return this->Type;
}
