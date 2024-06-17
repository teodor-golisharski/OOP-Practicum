#include "Account.h"
#include <iostream>
#include <ctime>

char Account::generate_random_number(unsigned int& seed) {
	const char charset[] = "0123456789";
	const size_t max_index = sizeof(charset) - 1;
	seed = seed * 1103515245 + 12345;
	return charset[(seed / 65536) % max_index];
}

void Account::copyFrom(const Account& other) {

	strcpy_s(this->account_number, ACCOUNT_NUMBER_LENGTH + 1, other.account_number);

	size_t size = strlen(other.bank_name) + 1;
	this->bank_name = new char[size];
	strcpy_s(bank_name, size, other.bank_name);

	this->balance = other.balance;
}

void Account::moveFrom(Account&& other) {

	for (size_t i = 0; i < ACCOUNT_NUMBER_LENGTH + 1; i++) {
		account_number[i] = other.account_number[i];
	}
	*other.account_number = 0;

	bank_name = other.bank_name;
	other.bank_name = nullptr;

	balance = other.balance;
}

void Account::free() {
	delete[] bank_name;
}

Account::Account() = default;

Account::Account(char account_number[ACCOUNT_NUMBER_LENGTH + 1], char* bank_name, double balance) {

	account_number[0] = 'B';
	account_number[1] = 'G';
	unsigned int seed = static_cast<unsigned int>(std::time(0));
	for (size_t i = 2; i < ACCOUNT_NUMBER_LENGTH + 1; i++) {
		account_number[i] = generate_random_number(seed);
	}

	if (!bank_name) {
		delete[] this->bank_name;
		throw std::invalid_argument("Bank name cannot be empty!");
	}
	size_t size = strlen(bank_name) + 1;
	strcpy_s(this->bank_name, size, bank_name);

	this->balance = balance;
}

Account::Account(const Account& other) {
	copyFrom(other);
}

Account::Account(Account&& other) noexcept {
	moveFrom(std::move(other));
}

Account& Account::operator=(const Account& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Account& Account::operator=(Account&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

const char* Account::get_account_number() const {
	return this->account_number;
}

const double Account::get_balance() const {
	return this->balance;
}

void Account::set_balance(double new_balance) {
	this->balance = new_balance;
}

const char* Account::get_bank_name() const {
	return this->bank_name;
}

Account::~Account() {
	free();
}