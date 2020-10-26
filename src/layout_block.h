#ifndef LAYOUT_BLOCK_H
#define LAYOUT_BLOCK_H

#include "abstract_multi_block.h"
#include "i_styled_block.h"
#include <QLinkedList>
#include <QString>

class Style;

class Layout_Block : public Abstract_Multi_Block, I_Styled_Block {
 public:
	Layout_Block(Style* style, bool loaded_from_document_file = true);
	QString to_backend_code();

 private:
	void initialize_from_style_layout();
	Abstract_Block* create_sub_block(Style* style);
};

#endif // LAYOUT_BLOCK_H
