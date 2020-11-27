#include "escaper.h"
#include "joed.h"
#include "lua_client.h"

Escaper::Escaper(Lua_VM* lua_vm) {
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Escaper::parse(QString escape_spec_line) {
	this->escape_table.append(this->lua_client->eval_inline_array_expr(escape_spec_line, 2));
}

QString Escaper::escape(QString text) {
	// Direct escaping will fail in cases like the below one:
	// While for ConTeXt '{'s and '}'s have to be escaped like this: \{ and \}, '\'s have to be
	// replaced by \textbackslash{}. There is than a circular dependancy which will always return
	// wrong results, no matter if we escape first the '{'s '}'s or replace first the '\'s in the
	// text. An easy solution to avoid such collisions is to replace each sources by a token, and
	// then replace each token by the corresponding destination
	const int UTF16_First_Private_Use_Character = 0xE000;
	int current_token = UTF16_First_Private_Use_Character;
	QString corrected_text = text;
	for (QStringList escape_pair : this->escape_table) {
		corrected_text = corrected_text.replace(escape_pair[0], QChar(current_token));
		current_token++;
	}
	current_token = UTF16_First_Private_Use_Character;
	for (QStringList escape_pair : this->escape_table) {
		corrected_text = corrected_text.replace(QChar(current_token), escape_pair[1]);
		current_token++;
	}
	return corrected_text;
}

Escaper::~Escaper() = default;
