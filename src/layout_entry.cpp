#include "layout_entry.h"
#include "style_properties.h"

Layout_Entry::Layout_Entry(Style* style) {
	this->the_style = style;
}

Style* Layout_Entry::style() {
	return this->the_style;
}
