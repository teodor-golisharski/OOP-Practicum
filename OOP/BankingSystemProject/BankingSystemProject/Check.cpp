#include "Check.h"

#include <iostream>
#include "BasicVector.hpp"
#include "ErrorMessages.hpp"
#include "Bank.h"

BasicVector<char*> Check::codes_in_use{};

char Check::generate_random_char(unsigned int& seed) {
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const size_t max_index = sizeof(charset) - 1;
	seed = seed * 1103515245 + 12345;
	return charset[(seed / 65536) % max_index];
}

// 2FA logic
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
bool Check::is_unique(char* code) {
	for (size_t i = 0; i < codes_in_use.size(); i++) {
		if (this->code == codes_in_use[i]) {
			return false;
		}
	}
	return true;
}
bool Check::verify_check_code(char* code){
	return (is_correct_format(code) && is_alpha_numeric(code) && is_unique(code));
}

Check::Check() = default;

Check::Check(double sum, const MyString& bank_name, const char* egn) {
	
	if (sum == 0)
		throw std::invalid_argument(EMPTY_FIELD);
	this->transaction_sum = sum;

	if (bank_name == "")
		throw std::invalid_argument(EMPTY_FIELD);

	if (!egn || strlen(egn) != EGN_LENGTH)
		throw std::invalid_argument("Egn must be exactly 10 digits!");

	// TO DO: validate that the bank has a client with this egn
	strcpy_s(this->egn, EGN_LENGTH + 1, egn);

	unsigned int seed = static_cast<unsigned int>(std::time(0));
	while (true) {
		for (size_t i = 0; i < CODE_LENGTH; i++)
			this->code[i] = generate_random_char(seed);
		if (is_unique(code)) {
			strcpy_s(this->code, CODE_LENGTH + 1, code);
			codes_in_use.push(code);
			break;
		}
	}
	
}



const double Check::get_tansaction_sum() const {
	return this->transaction_sum;
}

const MyString Check::get_bank_name() const {
	return this->bank_name;
}

const char* Check::get_egn() const {
	return this->egn;
}

const char* Check::get_code() const {
	return this->code;
}

Check::~Check() {
	for (size_t i = 0; i < codes_in_use.size(); i++) {
		if (this->code == codes_in_use[i]) {
			codes_in_use.delete_at(i);
			break;
		}
	}
}