#include "focus_manager.h"
#include "block_widget.h"
#include "text_edit.h"

Focus_Manager::Focus_Manager() {}

int Focus_Manager::level_of(QWidget* widget) {
	switch (type_of[widget]) {
	case BLOCK_WIDGET:
		return ((Block_Widget*)widget)->level();
	case TEXT_EDIT:
		return ((Text_Edit*)widget)->level();
	default: // Should not happen
		assert(false);
	}
}

// '%' is a remainder, not a modulo operation. When 'a' is negative, so will be the remainder
int mod(int a, int b) {
	int ret = a % b;
	if (ret < 0) ret += b;
	return ret;
}

QWidget* Focus_Manager::get_neighboor(QWidget* widget, bool search_next, int type) {
	int index = this->table.indexOf(widget);
	int delta = -1;
	if (search_next) {
		delta = 1;
	}
	while (true) {
		index = mod(index + delta, this->table.length());
		if (type == UNDEFINED || this->type_of[this->table[index]] == type) {
			return this->table[index];
		}
	}
}

QWidget* Focus_Manager::next_widget_after(QWidget* widget) {
	QWidget* next_widget = widget;
	while (true) {
		next_widget = this->get_neighboor(next_widget, true);
		if (level_of(next_widget) <= level_of(widget)) {
			return next_widget;
		}
	}
}

void Focus_Manager::insert(QWidget* widget, QWidget* next_widget, int type) {
	this->type_of[widget] = type;
	if (next_widget == nullptr) {
		this->table.append(widget);
		return;
	}
	this->table.insert(this->table.indexOf(next_widget), widget);
}

void Focus_Manager::focus_neighboor(QWidget* current_focus_widget, bool search_next) {
	this->get_neighboor(current_focus_widget, search_next, TEXT_EDIT)->setFocus();
}
