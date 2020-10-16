#ifndef MULTI_BLOCK_H
#define MULTI_BLOCK_H

#include "abstract_block.h"
#include <QLinkedList>
#include <QString>

class Multi_Block : public Abstract_Block {
 public:
	Multi_Block(Style* style);
	QString Compile();
	void Add_Child(Abstract_Block* child);

 private:
	QLinkedList<Abstract_Block*> first_child;
};

#endif // MULTI_BLOCK_H
