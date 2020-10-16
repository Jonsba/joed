#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

class Style;

class Layout_Entry {
	friend class Styles;

 public:
	Layout_Entry();
	Layout_Entry* Next();
	Style* style();
	bool is_children_block();

 private:
	Style* the_style;
	Layout_Entry* next = nullptr;
};

#endif // LAYOUT_NODE_H
