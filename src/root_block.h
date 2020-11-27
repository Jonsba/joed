#ifndef ROOT_BLOCK_H
#define ROOT_BLOCK_H

#include "layout_block.h"

class Writer;

class Root_Block : public Layout_Block {
 public:
	Root_Block(Style* style, bool auto_built);
	void save(Writer* writer);
	QString translate(Escaper* escaper);

 private:
	void initialize_from_style_layout();
};

#endif // ROOT_BLOCK_H
