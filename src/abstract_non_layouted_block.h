#ifndef ABSTRACT_NON_LAYOUTED_BLOCK_H
#define ABSTRACT_NON_LAYOUTED_BLOCK_H

#include "abstract_multi_block.h"

class Style;

class Abstract_Non_Layouted_Block : public Abstract_Multi_Block {
 public:
	Abstract_Non_Layouted_Block(QString identifier, Block_Type type, bool auto_built);
	virtual QString translate() override;
};

#endif // ABSTRACT_NON_LAYOUTED_BLOCK_H
