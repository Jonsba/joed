#ifndef MULTI_BLOCK_H
#define MULTI_BLOCK_H

#include "abstract_block.h"
#include <QLinkedList>
#include <QString>

class Multi_Block : public Abstract_Block {
 public:
	Multi_Block(Style* the_style);
	QString to_backend_code();
	void add_block(Abstract_Block* block);

 private:
	QLinkedList<Abstract_Block*> blocks;
};

#endif // MULTI_BLOCK_H
