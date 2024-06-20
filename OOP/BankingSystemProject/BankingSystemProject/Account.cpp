#include "Account.h"
#include <iostream>
#include <ctime>

char Account::generate_random_number(unsigned int& seed) {
	const char charset[] = "0123456789";
	const size_t max_index = sizeof(charset) - 1;
	seed = seed * 1103515245 + 12345;
	return charset[(seed / 65536) % max_index];
}

Account::Account() = default;

Account::Account(MyString bank_name) {

	account_number[0] = 'B';
	account_number[1] = 'G';
	unsigned int seed = static_cast<unsigned int>(std::time(0));
	for (size_t i = 2; i < ACCOUNT_NUMBER_LENGTH + 1; i++) {
		account_number[i] = generate_random_number(seed);
	}

	if (bank_name == "")
		throw std::invalid_argument("Bank name cannot be empty!");
	this->bank_name = bank_name;

	this->balance = 0;
}

const char* Account::get_account_number() const {
	return this->account_number;
}

const double Account::get_balance() const {
	return this->balance;
}

const MyString Account::get_bank_name() const {
	return bank_name;
}