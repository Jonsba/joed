#include "layout_entry.h"
#include "style.h"

Layout_Entry::Layout_Entry() {}

Style* Layout_Entry::Get_Style() {
	return this->style;
}

Layout_Entry* Layout_Entry::Next() {
	return this->next;
}

bool Layout_Entry::Is_Children_Block() {
	if (this->style->Get_Name() == Children_Block_Value) {
		return true;
	}
	return false;
}
