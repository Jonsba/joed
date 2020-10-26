#ifndef ABSTRACT_MULTI_BLOCK_H
#define ABSTRACT_MULTI_BLOCK_H

#include "abstract_block.h"
#include <QLinkedList>

// TODO: make it abstract
class Abstract_Multi_Block : public Abstract_Block {
 public:
	Abstract_Multi_Block(QString Identifier, Block_Type Type);
	void add_block(Abstract_Block* block);
	QLinkedList<Abstract_Block*> blocks();

 protected:
	QLinkedList<Abstract_Block*> the_blocks;
};

#endif // ABSTRACT_MULTI_BLOCK_H
