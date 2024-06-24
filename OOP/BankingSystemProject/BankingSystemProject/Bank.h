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
	unsigned last_task_index = 0;

	unsigned find_account(const char* account_number) const;
public:
	Bank();
	Bank(const MyString&name);

	unsigned get_task_index();

	const MyString& get_bank_name() const;

	void assign_task(Task new_task);
};