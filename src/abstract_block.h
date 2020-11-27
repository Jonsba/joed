#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include "style.h"

#include <QString>

class Escaper;
class Writer;

class Abstract_Block {
 public:
	Abstract_Block(Style* block_type);
	virtual ~Abstract_Block();
	const Style* style();
	virtual QString translate(Escaper* escaper) = 0;
	virtual void save(Writer* writer, int level) = 0;
	//

 protected:
	const Style* The_Style;
};

#endif // ABSTRACT_BLOCK_H
