#include<iostream>
#include "Client.h"

void Client::add_account(const Account& account) {
	this->accounts.push(account);
}
void Client::remove_account(const char* accountNumber) {
	unsigned index = find_account_index(accountNumber);
	this->accounts.delete_at(index);
}
void Client::redeem_check(const char* verification_code, Account& account) {
	unsigned index = 0;
	bool flag = false;
	for (unsigned i = 0; i < checks.size(); i++)
	{
		if (strcmp(checks[i].get_code(), verification_code) == 0) {

			account.deposit(checks[i].get_tansaction_sum());
			index = i;
			flag = true;
			break;
		}
	}
	if (flag) {
		checks.delete_at(index);
	}
	else {
		throw std::runtime_error(WRONG_VERIFICATION);
	}
}

unsigned Client::find_account_index(const char* account_number) const {

	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (strcmp(accounts[i].get_account_number(), account_number) == 0) {
			return i;
		}
	}
	return -1;

}
Account& Client::find_account(const char* account_number) const {

	unsigned index = find_account_index(account_number);
	if (index != -1) {
		return accounts[index];
	}
	throw std::invalid_argument(ACCOUNT_NOT_FOUND);
}

Client::~Client() = default;
Client::Client() = default;
Client::Client(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password)
	: User(name, egn, age, password, UserRole::client) {}

BasicVector<Account> Client::get_accounts(const MyString& bank_name) const {

	BasicVector<Account> result;
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (bank_name == accounts[i].get_bank_name()) {
			result.push(accounts[i]);
		}
	}
	return result;
}
unsigned Client::get_messages_count() const {
	return messages.size();
}
MyString Client::get_message_at_index(unsigned index) const {
	if (index < messages.size()) {
		return messages[index];
	}
}

void Client::help() const {
	std::cout << "----------------------------------------------------------------------------\n";
	std::cout << "Client commands:\n";
	std::cout << " * check_avl [bank_name] [account_number] - Check account balance\n";
	std::cout << " * open [bank_name] - Open a new account\n";
	std::cout << " * close [bank_name] [account_number] - Close an account\n";
	std::cout << " * redeem [bank_name] [account_number] [verification_code] - Redeem a check\n";
	std::cout << " * change [new_bank_name] [current_bank_name] [account_number] - Change bank\n";
	std::cout << " * list [bank_name] - List all accounts\n";
	std::cout << " * messages - Show all messages\n";
	std::cout << " * exit - Logout\n";
	std::cout << " * whoami - Show current user information\n";
	std::cout << " * help - Show this help menu\n";
	std::cout << "----------------------------------------------------------------------------\n";
}
bool Client::has_accounts_in_bank(const MyString& bank_name) {
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].get_bank_name() == bank_name) {
			return true;
		}
	}
	return false;
}
bool Client::has_account(const MyString& account_number) const {
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].get_account_number() == account_number) {
			return true;
		}
	}
	return false;
}

void Client::receive_check(const Check& check) {
	checks.push(check);
}
void Client::receive_message(const MyString& message) {
	messages.push(message);
}

void Client::transfer_checks(const MyString& old_bank, const MyString& new_bank) {
	
	if (!has_accounts_in_bank(old_bank)) {
		for (unsigned i = 0; i < checks.size(); i++)
		{
			checks[i].set_bank_name(new_bank);
		}
	}
}

