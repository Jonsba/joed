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
	Layout_Block(Style* style, Escaper* escaper, bool loaded_from_document_file = true);
	QString translate();

 protected:
	QString translate(QHash<QString, QString> global_dict);
	Style* style;

 private:
	void initialize_from_style_layout();
	Abstract_Block* create_sub_block(Style* style);
	//
	Escaper* escaper;
};

#endif // LAYOUT_BLOCK_H
