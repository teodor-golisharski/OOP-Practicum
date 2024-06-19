#include "Bank.h"
#include "Client.h"
#include <iostream>

void Bank::free() {
	delete[] name;
	name = nullptr;
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
Bank::Bank(const Bank& other) {
	copyFrom(other);
}
Bank::Bank(Bank&& other) noexcept {
	moveFrom(std::move(other));
}

void Bank::copyFrom(const Bank& other) {
	size_t len = strlen(name) + 1;
	this->name = new char[len];
	strcpy_s(this->name, len, name);

	this->accounts = other.accounts;
}
void Bank::moveFrom(Bank&& other) {

	this->name = other.name;
	this->accounts = std::move(other.accounts);

	other.name = nullptr;
}


Bank& Bank::operator=(Bank&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
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
unsigned Bank::find_account(const char* account_number) const{
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (strcmp(accounts[i].get_account_number(), account_number) == 0) {
			return i;
		}
	}
	return -1;
}

void Bank::open_account(Client& client) {
	Account account(this->name);
	//client.add_account(account);
	
	this->accounts.push(account);
}

void Bank::close_account(Client& client, const char* account_number) {
	unsigned index = find_account(account_number);
	this->accounts.delete_at(index);

	index = client.find_account(account_number);
	client.accounts.delete_at(index);	
}

