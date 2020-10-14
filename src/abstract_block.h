#ifndef BLOCK_CONTENT_H
#define BLOCK_CONTENT_H

#include <QString>

class Style;

class Abstract_Block {
 public:
	Abstract_Block(Style* style);
	Style* Get_Style();
	virtual QString Backend_Contents() = 0;

 protected:
	QString joed_name;
	Style* style;
};

#endif // BLOCK_CONTENT_H
