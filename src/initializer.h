#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "abstract_buildable_object.h"
#include "joed.h"

#include <QHash>
#include <QString>
#include <QVector>

// HEADER

enum State { Starting, Parsing_Key, Parsing_Value };

template <class Buildable_Object> class Initializer {
 public:
	Initializer(QString_Vector Intermediate_Keys, QString_Vector End_Keys);
	State parse_identifier(QString identifier);
	void add_value(QString value);
	Buildable_Object* built_object();

 private:
	QString_Vector Intermediate_Keys;
	QString_Vector End_Keys;
	Buildable_Object* the_object;
	QString current_identifier = "";
};

// IMPLEMENTATION
// See:
// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template <class Buildable_Object>
Initializer<Buildable_Object>::Initializer(QString_Vector Intermediate_Keys,
                                           QString_Vector End_Keys) {
	static_assert(std::is_base_of<Abstract_Buildable_Object, Buildable_Object>::value,
	              "type parameter of this class must derive from Abstract_Built_Object");
	this->Intermediate_Keys = Intermediate_Keys;
	this->End_Keys = End_Keys;
	this->the_object = new Buildable_Object();
}

template <class Buildable_Object>
State Initializer<Buildable_Object>::parse_identifier(QString identifier) {
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

template <class Buildable_Object> void Initializer<Buildable_Object>::add_value(QString value) {
	this->the_object->assign(this->current_identifier, value);
}
template <class Buildable_Object> Buildable_Object* Initializer<Buildable_Object>::built_object() {
	return this->the_object;
}

#endif // INITIALIZER_H
