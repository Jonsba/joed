#include "environment.h"
#include "lua_client.h"

Environment::Environment(Lua_VM* lua_vm) {
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Environment::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	if (end_key != Field::Key::Output) {
		throw Exceptions::Invalid_Key();
	}
	this->lua_client->add_expr_line(value, is_first_value_line);
}

QString Environment::translate() {
	return this->lua_client->eval_expr();
}

Environment::~Environment() = default;
