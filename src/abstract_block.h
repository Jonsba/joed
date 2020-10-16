#ifndef BLOCK_CONTENT_H
#define BLOCK_CONTENT_H

#include <QLinkedList>
#include <QString>

class Style;

class Abstract_Block {
 public:
	Abstract_Block(Style* the_style);
	Style* style();
	virtual QString compile() = 0;

 protected:
	Style* the_style;
	// QLinkedList<Abstract_Block*> first_sibling;
};

#endif // BLOCK_CONTENT_H
