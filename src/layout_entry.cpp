#include "layout_entry.h"
#include "style.h"

Layout_Entry::Layout_Entry(Style* the_style) {
	this->the_style = the_style;
}

Style* Layout_Entry::style() {
	return this->the_style;
}

bool Layout_Entry::is_children_entry() {
	if (this->style() == nullptr) {
		return true;
	}
	return false;
}
