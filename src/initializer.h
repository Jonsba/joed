#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "abstract_loadable_object.h"
#include "joed.h"

#include <QHash>
#include <QString>
#include <QVector>

// HEADER

enum State { Starting, Parsing_Key, Parsing_Value };

template <class Loadable_Object> class Initializer {
 public:
	Initializer(QString_Vector Intermediate_Keys, QString_Vector End_Keys);
	State parse_identifier(QString identifier);
	void add_value(QString value);
	Loadable_Object* loaded_object();

 private:
	QString_Vector Intermediate_Keys;
	QString_Vector End_Keys;
	Loadable_Object* the_object;
	QString current_identifier = "";
};

// IMPLEMENTATION
// See:
// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template <class Loadable_Object>
Initializer<Loadable_Object>::Initializer(QString_Vector Intermediate_Keys,
                                          QString_Vector End_Keys) {
	static_assert(std::is_base_of<Abstract_Loadable_Object, Loadable_Object>::value,
	              "type parameter of this class must derive from Abstract_Built_Object");
	this->Intermediate_Keys = Intermediate_Keys;
	this->End_Keys = End_Keys;
	this->the_object = new Loadable_Object();
}

template <class Loadable_Object>
State Initializer<Loadable_Object>::parse_identifier(QString identifier) {
	if (identifier == "") {
		return Parsing_Value;
	}
	State next_state = Parsing_Value;
	int index = this->End_Keys.indexOf(identifier);
	if (index == -1) {
		index = this->Intermediate_Keys.indexOf(identifier);
		if (index == -1) {
			print("Unknow identifier: " + identifier);
			throw;
		}
		next_state = Parsing_Key;
		this->the_object->process_intermediate_key(identifier);
	}
	this->current_identifier = identifier;
	return next_state;
}

template <class Loadable_Object> void Initializer<Loadable_Object>::add_value(QString value) {
	this->the_object->assign(this->current_identifier, value);
}
template <class Loadable_Object> Loadable_Object* Initializer<Loadable_Object>::loaded_object() {
	return this->the_object;
}

#endif // INITIALIZER_H
