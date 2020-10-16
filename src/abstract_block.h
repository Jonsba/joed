#ifndef BLOCK_CONTENT_H
#define BLOCK_CONTENT_H

#include <QLinkedList>
#include <QString>

class Style;

class Abstract_Block {
 public:
	Abstract_Block(Style* style);
	Style* Get_Style();
	virtual QString Compile() = 0;

 protected:
	Style* style;
	// QLinkedList<Abstract_Block*> first_sibling;
};

#endif // BLOCK_CONTENT_H
