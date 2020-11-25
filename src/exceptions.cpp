#include "exceptions.h"

Exception::Exception(QString msg) {
	this->msg = msg;
}
Exception::Exception(Exception_Code code, QString msg) {
	this->code = code;
	this->msg = msg;
}
