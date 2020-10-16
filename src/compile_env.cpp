#include "compile_env.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"

Compile_Env::Compile_Env() {}

void Compile_Env::process_intermediate_key(QString key) {}

void Compile_Env::assign(QString end_key, QString value) {
	if (end_key == Name_Key) {
		this->the_backend_name = value;
	} else if (end_key == Exec_Key) {
		this->the_backend_exec = value;
	} else {
		print("Unknown backend key: " + end_key + " = " + value);
		throw;
	}
}

QString Compile_Env::backend_name() {
	return this->the_backend_name;
}

QString Compile_Env::backend_exec() {
	return this->the_backend_exec;
}
