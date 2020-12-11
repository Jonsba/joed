#ifndef WIDGETS_H
#define WIDGETS_H

class Focus_Manager;

class QScrollArea;
class QWidget;

struct Widgets {
	QWidget* parent;
	QScrollArea* scroll_area;
	Focus_Manager* focus_manager;
	QWidget* next_widget_in_focus = nullptr;
};

#endif // WIDGETS_H
