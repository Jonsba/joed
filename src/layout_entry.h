#ifndef LAYOUT_ENTRY_H
#define LAYOUT_ENTRY_H

class Style;

class Layout_Entry {

 public:
	Layout_Entry(Style* the_style);
	Style* style();
	bool is_children_entry();

 private:
	Style* the_style;
};

#endif // LAYOUT_ENTRY_H
