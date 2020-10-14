#ifndef MULTI_BLOCK_H
#define MULTI_BLOCK_H

#include "abstract_block.h"
#include <QString>
#include <QVector>

class Multi_Block : public Abstract_Block {
 public:
	Multi_Block(Style* style);
	QString Backend_Contents();
	void Add_Child(Abstract_Block* child);
	void Add_Sibling(Abstract_Block* sibling);

 private:
	QVector<Abstract_Block*> first_child;
	QVector<Abstract_Block*> first_sibling;
};

#endif // MULTI_BLOCK_H
