#pragma once
#include "Account.h"
#include "Employee.h"
#include "Check.h"
#include "Client.h"
#include "BasicVector.hpp"
#include "MyString.hpp"

class Bank {
private:
	MyString name;
	BasicVector<Account> accounts;
	BasicVector<Employee> employees;

	unsigned find_account(const char* account_number) const;
public:
	Bank();
	Bank(const MyString&name);

	const MyString& get_bank_name() const;
	void open_account(Client& client);
	void close_account(Client& client, const char* account_number);
};