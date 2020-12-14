#ifndef FOCUS_MANAGER_H
#define FOCUS_MANAGER_H

#include <QHash>
#include <QVector>

class QWidget;

class Block_Widget;

#define UNDEFINED 0
#define BLOCK_WIDGET 1
#define TEXT_EDIT 2
#define CHILDREN_WIDGET 3

class Focus_Manager {
 public:
	Focus_Manager();
	QWidget* next_widget_after(QWidget* widget, int type = UNDEFINED);
	void insert(QWidget* widget, QWidget* next_widget, int type);
	void remove(QWidget* widget);
	void focus_neighboor(QWidget* current_focus_widget, bool search_next = true);

 private:
	QWidget* get_neighboor(QWidget* widget, bool search_next, int type = UNDEFINED);
	int level_of(QWidget* widget);
	//
	QVector<QWidget*> table;
	QHash<QWidget*, int> type_of;
};

#endif // FOCUS_MANAGER_H
