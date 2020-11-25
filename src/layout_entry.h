#ifndef LAYOUT_ENTRY_H
#define LAYOUT_ENTRY_H

#include "styles.h"

class Layout_Entry {

 public:
	Layout_Entry(Style* style);
	Style* style();

 private:
	Style* the_style;
};

#endif // LAYOUT_ENTRY_H
