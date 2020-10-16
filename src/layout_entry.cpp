#include "layout_entry.h"
#include "style.h"

Layout_Entry::Layout_Entry() {}

Style* Layout_Entry::style() {
	return this->the_style;
}

Layout_Entry* Layout_Entry::Next() {
	return this->next;
}

bool Layout_Entry::is_children_block() {
	if (this->the_style->name() == Children_Block_Value) {
		return true;
	}
	return false;
}
