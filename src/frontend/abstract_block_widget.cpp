#include "abstract_block_widget.h"
#include "focus_manager.h"

Abstract_Block_Widget::Abstract_Block_Widget(Widgets widgets, int type, int level)
    : QWidget(widgets.parent) {
	this->the_level = level;
	widgets.focus_manager->insert(this, widgets.next_widget_in_focus, type);
}

int Abstract_Block_Widget::level() {
	return this->the_level;
}
