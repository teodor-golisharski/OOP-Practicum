#include "Bank.h"
#include "Client.h"
#include <iostream>

Bank::Bank() = default;
Bank::~Bank() = default;

Bank::Bank(const MyString& name) {
	this->name = name;
}


const MyString& Bank::get_bank_name() const {
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
	//Account account(this->name);
	//client.add_account(account);
	
	//this->accounts.push(account);
}

void Bank::close_account(Client& client, const char* account_number) {
	/*unsigned index = find_account(account_number);
	this->accounts.delete_at(index);

	index = client.find_account(account_number);
	client.accounts.delete_at(index);	*/
}

