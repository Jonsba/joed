#ifndef ABSTRACT_MULTI_BLOCK_H
#define ABSTRACT_MULTI_BLOCK_H

#include "abstract_block.h"

class Abstract_Multi_Block : public Abstract_Block {
 public:
	Abstract_Multi_Block(Style* style, bool auto_built);
	~Abstract_Multi_Block();
	// append_child is meant to only be called by constructor of a derived class. Afterwards children
	// will be inserted via Abstract_Block::insert_sibling. At that point, the last_child_tmp pointer
	// may not point to the correct element, but it won't be needed anymore.
	Abstract_Block* append_child(Style* style);
	void append_child(Abstract_Block* block);
	Abstract_Block* first_child();
	void reset_first_child(Abstract_Block* new_first_child);
	virtual QString translate(Escaper* escaper) override;
	virtual void save(Writer* writer, int level) override;

 protected:
	bool auto_built;
	Abstract_Block* the_first_child = nullptr;

 private:
	Abstract_Block* last_child_tmp = nullptr;
};

#endif // ABSTRACT_MULTI_BLOCK_H
