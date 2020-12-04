#include "children_block.h"
#include "field.h"
#include "joed.h"
#include "layout_block.h"
#include "styles.h"
#include "text_block.h"

Children_Block::Children_Block(Abstract_Multi_Block* parent, bool auto_built)
    : Abstract_Multi_Block(Styles::Children_Style, parent, auto_built) {}
