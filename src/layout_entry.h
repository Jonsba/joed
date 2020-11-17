#ifndef LAYOUT_ENTRY_H
#define LAYOUT_ENTRY_H

#include "abstract_block.h"

class Style;

class Layout_Entry {

 public:
	Layout_Entry(Style* the_style);
	Style* style();
	Block_Type type();

 private:
	Style* the_style;
};

#endif // LAYOUT_ENTRY_H
