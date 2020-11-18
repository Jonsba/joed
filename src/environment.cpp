#include "environment.h"
#include "abstract_block.h"
#include "lua_client.h"

Environment::Environment(Lua_VM* lua_vm) {
	this->lua_client.reset(new Lua_Client(lua_vm));
}

Parse_State Environment::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Field::Key::Name) {
		this->name = value;
	} else if (end_key == Field::Key::Output) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	} else {
		return Parse_State::Invalid_Key_E;
	}
	return Parse_State::Success_E;
}

QString Environment::translate() {
	return this->lua_client->eval_expr();
}

Environment::~Environment() = default;
