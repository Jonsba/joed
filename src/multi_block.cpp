#include "multi_block.h"
#include "joed.h"
#include "lua_vm.h"
#include "style.h"

Multi_Block::Multi_Block(Style* style) : Abstract_Block(style) {}

void Multi_Block::add_block(Abstract_Block* child) {
	this->blocks.append(child);
}

QString Multi_Block::to_backend_code() {
	QString child_contents = "";
	for (Abstract_Block* child_block : this->blocks) {
		child_contents += child_block->to_backend_code();
	}
	// At the moment, the children block is the only one there. It needs to be fixed later to allow
	// other blocks
	Global_Dict global_dict;
	global_dict[Style::Children_Block_Value] = child_contents;
	return this->the_style->compile(global_dict);
}
