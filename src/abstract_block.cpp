#include "abstract_block.h"
#include "field.h"
#include "writer.h"

Abstract_Block::Abstract_Block(QString identifier, Block_Type type)
    : Identifier(identifier), Type(type) {}

QString Abstract_Block::identifier() {
	return this->Identifier;
}

Block_Type Abstract_Block::type() {
	return this->Type;
}

Abstract_Block::~Abstract_Block() = default;
