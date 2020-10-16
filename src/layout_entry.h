#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

class Style;

class Layout_Entry {

 public:
	Layout_Entry(Style* the_style);
	Style* style();
	bool is_children_block();

 private:
	Style* the_style;
};

#endif // LAYOUT_NODE_H
