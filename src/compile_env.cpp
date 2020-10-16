#include "compile_env.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"

Compile_Env::Compile_Env() {}

void Compile_Env::Set_Backend(QString backend) {
	this->backend = backend;
}

QString Compile_Env::Get_Backend() {
	return this->backend;
}
