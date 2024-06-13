#include "Bank.h"
#include <iostream>

Bank::Bank() = default;
Bank::~Bank() {
	delete[] name;
}

Bank::Bank(const char* name) {
	size_t len = strlen(name) + 1;
	this->name = new char[len];
	strcpy_s(this->name, len, name);
}

void Bank::copyFrom(const Bank& other) {

}

const char* Bank::get_bank_name() const {
	return this->name;
}

