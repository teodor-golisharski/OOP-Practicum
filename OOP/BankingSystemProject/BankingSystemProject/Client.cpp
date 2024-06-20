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

Client::Client(const char* name, const char* egn, unsigned age, const char* password) 
	: User(name, egn, age, password, UserRole::client) {}


double Client::check_avl(const char* bank_name, unsigned account_number) const{
	return 1;
}


