#ifndef ABSTRACT_MULTI_BLOCK_H
#define ABSTRACT_MULTI_BLOCK_H

#include "abstract_block.h"

class Abstract_Multi_Block : public Abstract_Block {
 public:
	Abstract_Multi_Block(Style* style, bool auto_built);
	~Abstract_Multi_Block();
	Abstract_Block* append_child(Style* style);
	void append_child(Abstract_Block* block);
	Abstract_Block* first_child();
	virtual QString translate(Escaper* escaper) override;
	virtual void save(Writer* writer, int level) override;

 protected:
	bool auto_built;
	QString Blocks_Identifier; // const
	Abstract_Block* the_first_child = nullptr;
	Abstract_Block* last_child = nullptr;
};

#endif // ABSTRACT_MULTI_BLOCK_H
