#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include <QString>

class Abstract_Multi_Block;
class Escaper;
struct Style;
class Writer;

class Abstract_Block {

 public:
	Abstract_Block(Style* style);
	virtual ~Abstract_Block();
	Style* style();
	virtual QString translate(Escaper* escaper) = 0;
	virtual void save(Writer* writer, int level) = 0;
	Abstract_Block* insert_sibling(Style* style, bool insert_after, bool auto_built);
	void insert_sibling(Abstract_Block* block, bool insert_after);
	Abstract_Multi_Block* parent();
	void set_parent(Abstract_Multi_Block* parent);
	Abstract_Block* next();

 protected:
	// This function is created for 2 uses cases:
	// 1) Creation of a child block (in which case parent = this)
	// 2) Creation of a sibling block (in which case parent = this->parent)
	Abstract_Block* make_block(Style* style, bool auto_built);
	//
	Style* the_style;
	Abstract_Multi_Block* the_parent = nullptr;
	Abstract_Block* the_next = nullptr;
	Abstract_Block* previous = nullptr;

 private:
	static void set_sibling_relationship(Abstract_Block* first, Abstract_Block* second);
};

#endif // ABSTRACT_BLOCK_H
