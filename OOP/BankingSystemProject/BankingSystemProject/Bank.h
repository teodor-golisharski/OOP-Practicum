#pragma once
#include "Account.h"
#include "Employee.h"
#include "Check.h"

class Bank {
private:
	char* name;
	Account* accounts;
	Employee* employees;
	Check* checks;
public:

	Account& find_account(const char* account_number);
	void open_account(//const User& client);
	void close_account(const char* account_number);

};