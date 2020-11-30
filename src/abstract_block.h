#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include "style.h"

#include <QString>

class Abstract_Multi_Block;
class Escaper;
class Writer;

class Abstract_Block {
 public:
	Abstract_Block(Style* block_type, Abstract_Multi_Block* parent);
	virtual ~Abstract_Block();
	const Style* style();
	virtual QString translate(Escaper* escaper) = 0;
	virtual void save(Writer* writer, int level) = 0;
	Abstract_Multi_Block* parent();
	Abstract_Block* next();
	void set_next(Abstract_Block* the_next);
	//

 protected:
	const Style* The_Style;
	Abstract_Multi_Block* the_parent;
	Abstract_Block* the_next = nullptr;
};

#endif // ABSTRACT_BLOCK_H
