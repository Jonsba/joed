#include "layout_entry.h"
#include "style.h"

Layout_Entry::Layout_Entry(Style* the_style) {
	this->the_style = the_style;
}

Style* Layout_Entry::style() {
	return this->the_style;
}

Block_Type Layout_Entry::type() {
	if (this->the_style == nullptr) {
		return Block_Type::Children_Block_E;
	}
	return this->the_style->type();
}
