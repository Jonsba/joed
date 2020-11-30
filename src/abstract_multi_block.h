#ifndef ABSTRACT_MULTI_BLOCK_H
#define ABSTRACT_MULTI_BLOCK_H

#include "abstract_block.h"

class Abstract_Multi_Block : public Abstract_Block {
 public:
	Abstract_Multi_Block(Style* style, Abstract_Multi_Block* parent, bool auto_built);
	~Abstract_Multi_Block();
	virtual Abstract_Block* create_block(Style* style) = 0;
	Abstract_Block* first_child();
	virtual QString translate(Escaper* escaper) override;
	virtual void save(Writer* writer, int level) override;

 protected:
	void add_child(Abstract_Block* block);
	//
	bool auto_built;
	QString Blocks_Identifier; // const
	Abstract_Block* the_first_child = nullptr;
	Abstract_Block* last_child = nullptr;
};

#endif // ABSTRACT_MULTI_BLOCK_H
