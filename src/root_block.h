#ifndef ROOT_BLOCK_H
#define ROOT_BLOCK_H

#include "layout_block.h"

class Style;
class Writer;

class Root_Block : public Layout_Block {
 public:
	Root_Block(Style* style, Escaper* escaper, bool auto_built);
	void save(Writer* writer);
	QString translate();

 private:
	void initialize_from_style_layout(Escaper* escaper);
};

#endif // ROOT_BLOCK_H
