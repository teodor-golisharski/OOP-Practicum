#include<iostream>
#include "Client.h"


unsigned Client::find_account(const char* account_number) const {
	
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].get_account_number() == account_number) {
			return i;
		}
	}
	throw std::invalid_argument("Account not found!");

}
Client::~Client() = default;

Client::Client() = default;

Client::Client(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password)
	: User(name, egn, age, password, UserRole::client) {}


double Client::check_avl(const MyString& bank_name, const char* account_number) const{
	return 1;
}

void Client::help() const  {
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
