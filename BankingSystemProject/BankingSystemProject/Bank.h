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

	void assign_task(Task& new_task);
	unsigned get_task_index();

	const MyString& get_bank_name() const;

	const char* open_account(Client& client, double sum);
	void close_account(Client& client, const char* account_number);

	Employee& get_employee(const MyString& egn) const;

	void add_employee(const Employee& employee);
	unsigned get_employees_count() const;
	void delete_task(unsigned id, Employee& employee);

};