#ifndef LAYOUT_BLOCK_H
#define LAYOUT_BLOCK_H

#include "abstract_multi_block.h"
#include <QHash>
#include <QLinkedList>
#include <QString>

class Style;
class Escaper;

class Layout_Block : public Abstract_Multi_Block {
 public:
	Layout_Block(Style* style, bool auto_built);
	QString translate() override;
	void save(Writer* writer, int level) override;
	// Undoes method shadowing
	using Abstract_Multi_Block::create_block;

 protected:
	QString translate(QHash<QString, QString> global_dict);
	Style* style;

 private:
	Abstract_Block* create_block(Block_Type type, Style* style, Escaper* escaper) override;
	//
};

#endif // LAYOUT_BLOCK_H
