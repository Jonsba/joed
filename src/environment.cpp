#include "environment.h"
#include "abstract_block.h"
#include "lua_client.h"

Environment::Environment(Lua_VM* lua_vm) {
	this->lua_client = new Lua_Client(lua_vm);
}

State Environment::process_key(QString key, int level) {
	return State::Parsing_Value;
}

void Environment::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Keys[Name_E]) {
		this->name = value;
	} else if (end_key == Keys[Output_E]) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	}
}

QString Environment::translate() {
	return this->lua_client->eval_expr();
}
