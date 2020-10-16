#include "compile_env.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"

Compile_Env::Compile_Env() {}

void Compile_Env::set_backend(QString backend) {
	this->the_backend = backend;
}

QString Compile_Env::backend() {
	return this->the_backend;
}
