#ifndef ABSTRACT_MULTI_BLOCK_H
#define ABSTRACT_MULTI_BLOCK_H

#include "abstract_block.h"
#include <QLinkedList>

class Style;
class Escaper;

class Abstract_Multi_Block : public Abstract_Block {
 public:
	Abstract_Multi_Block(QString identifier, Block_Type type, bool auto_built);
	~Abstract_Multi_Block();
	Abstract_Block* create_block(Block_Type type);
	Abstract_Block* create_block(Style* style);
	Abstract_Block* create_block(Style* style, Escaper* escaper);
	virtual Abstract_Block* create_block(Block_Type type, Style* style, Escaper* escaper) = 0;
	QLinkedList<Abstract_Block*> blocks();
	virtual QString translate() override;
	virtual void save(Writer* writer, int level) override;

 protected:
	void add_block(Abstract_Block* block);
	//
	bool auto_built;
	QString Blocks_Identifier; // const
	QLinkedList<Abstract_Block*> the_blocks;
};

#endif // ABSTRACT_MULTI_BLOCK_H
