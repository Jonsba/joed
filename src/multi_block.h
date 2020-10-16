#ifndef MULTI_BLOCK_H
#define MULTI_BLOCK_H

#include "abstract_block.h"
#include <QLinkedList>
#include <QString>

class Multi_Block : public Abstract_Block {
 public:
	Multi_Block(Style* the_style);
	QString compile();
	void add_child(Abstract_Block* child);

 private:
	QLinkedList<Abstract_Block*> children;
};

#endif // MULTI_BLOCK_H
