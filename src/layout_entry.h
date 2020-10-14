#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

class Style;

class Layout_Entry {
	friend class Styles;

 public:
	Layout_Entry();
	Layout_Entry* Next();
	Style* Get_Style();
	bool Is_Children_Block();

 private:
	Style* style;
	Layout_Entry* next = nullptr;
};

#endif // LAYOUT_NODE_H
