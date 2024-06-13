#include<iostream>
#include "Client.h"

void Client::free() {
	delete[] accounts;
	delete[] messages;

	messagesCount = 0;
	accountsCount = 0;
}

void Client::copyFrom(const Client& other) {
	accounts = new Account[other.accountsCount];
	accountsCount = other.accountsCount;
	for (size_t i = 0; i < accountsCount; i++)
	{
		accounts[i] = other.accounts[i];
	}

	messages = new Message[other.messagesCount];
	messagesCount = other.messagesCount;
	for (size_t i = 0; i < messagesCount; i++)
	{
		messages[i] = other.messages[i];
	}
}
void Client::moveFrom(Client&& other) {
	accounts = other.accounts;
	accountsCount = other.accountsCount;
	
	other.accounts = nullptr;
	other.accountsCount = 0;

	messages = other.messages;
	messagesCount = other.messagesCount;

	other.messages = nullptr;
	other.messagesCount = 0;
}

Account& Client::find_account(const char* account_number) const {
	
	for (size_t i = 0; i < accountsCount; i++)
	{
		if (accounts[i].get_account_number() == account_number) {
			return accounts[i];
		}
	}
	throw std::invalid_argument("Account not found!");
}

Client::Client() = default;
Client::Client(const char* name, const char* egn, unsigned age, const char* password) 
	: User(name, egn, age, password) {}

Client::Client(const Client& other) {
	copyFrom(other);
}

Client::Client(Client&& other) {
	moveFrom(std::move(other));
}

Client::~Client() {
	free();
}

double Client::check_avl(const char* bank_name, unsigned account_number) const{
	return 1;
}


