#include "Bank.h"
#include <iostream>

void Bank::free() {
	delete[] name;

}

Bank::Bank() = default;
Bank::~Bank() {
	free();
}

Bank::Bank(const char* name) {
	size_t len = strlen(name) + 1;
	this->name = new char[len];
	strcpy_s(this->name, len, name);
}

void Bank::copyFrom(const Bank& other) {
	size_t len = strlen(name) + 1;
	this->name = new char[len];
	strcpy_s(this->name, len, name);

	this->accounts = other.accounts;
	this->checks = other.checks;
	this->employees = other.employees;
}

Bank::Bank(const Bank& other) {
	copyFrom(other);
}

Bank& Bank::operator=(const Bank& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

const char* Bank::get_bank_name() const {
	return this->name;
}

Account* Bank::find_account(const char* account_number) {
	for (size_t i = 0; i < accounts.size(); i++)
	{
		if (strcmp(accounts[i].get_account_number(), account_number) == 0) {
			return &accounts[i];
		}
	}
	return nullptr;
}

void Bank::open_account(const User& client) {
	Account account;
}

void Bank::close_account(const char* account_number) {

}

