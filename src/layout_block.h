#ifndef LAYOUT_BLOCK_H
#define LAYOUT_BLOCK_H

#include "abstract_multi_block.h"

#include <QHash>

class Escaper;

class Layout_Block : public Abstract_Multi_Block {
 public:
	Layout_Block(Style* style, Abstract_Multi_Block* parent, bool auto_built);
	QString translate(Escaper* escaper) override;
	QString translate(Escaper* escaper, QHash<QString, QString> global_dict);
	void save(Writer* writer, int level) override;
};

#endif // LAYOUT_BLOCK_H
