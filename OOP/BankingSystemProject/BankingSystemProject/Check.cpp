#include "Check.h"

#include <iostream>
#include "BasicVector.hpp"

BasicVector<char*> Check::codes_in_use{};

bool Check::is_correct_format(char* code) {
	if (strlen(code) != CODE_LENGTH)
		return false;
	return true;
}

bool Check::is_alpha_numeric(char* code) {
	for (size_t i = 0; i < CODE_LENGTH; i++) {
		if (!isalnum(code[i]))
			return false;
	}
	return true;
}

bool Check::is_unique(char* code, BasicVector<char*> codes) {
	for (size_t i = 0; i < codes_in_use.size(); i++) {
		if (this->code == codes_in_use[i]) {
			return false;
		}
	}
	return true;
}

Check::Check() = default;

Check::Check(char* code, double sum) {

	if (!is_correct_format(code))
		throw std::invalid_argument("Check code must be of length 3!");
	if (!is_alpha_numeric(code))
		throw std::invalid_argument("Check code must only contain letters and numbers!");
	if (!is_unique(code, Check::codes_in_use))
		throw std::invalid_argument("This code is already in use!");
	for (size_t i = 0; i < CODE_LENGTH; i++)
		this->code[i] = code[i];
	codes_in_use.push(code);

	this->transaction_sum = sum;
}

const char* Check::get_check_code() const {
	return this->code;
}

const double Check::get_tansaction_sum() const {
	return this->transaction_sum;
}

Check::~Check() {
	for (size_t i = 0; i < codes_in_use.size(); i++) {
		if (this->code == codes_in_use[i]) {
			codes_in_use.delete_at(i);
			break;
		}
	}
}