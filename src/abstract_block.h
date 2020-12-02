#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include "style.h"

#include <QString>

class Abstract_Multi_Block;
class Escaper;
class Writer;

class Abstract_Block {
	friend class Abstract_Multi_Block;

 public:
	Abstract_Block(Style* block_type);
	virtual ~Abstract_Block();
	Style* style();
	virtual QString translate(Escaper* escaper) = 0;
	virtual void save(Writer* writer, int level) = 0;
	Abstract_Multi_Block* parent();
	Abstract_Block* insert_sibling(Style* style, bool auto_built);
	void insert_sibling(Abstract_Block* block);
	Abstract_Block* next();

 protected:
	Abstract_Block* make_block(Style* style, bool auto_built);
	//
	Style* the_style;
	Abstract_Block* the_next = nullptr;
};

#endif // ABSTRACT_BLOCK_H
