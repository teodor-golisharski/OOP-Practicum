#pragma once
#include "Account.h"
#include "Check.h"
#include "Client.h"
#include "BasicVector.hpp"
#include "MyString.hpp"

class Bank {
private:
	MyString name;
	BasicVector<Account> accounts;

	unsigned find_account(const char* account_number) const;
public:
	Bank();
	Bank(const MyString& name);
	~Bank();

	const MyString& get_bank_name() const;
	void open_account(Client& client);
	void close_account(Client& client, const char* account_number);
};