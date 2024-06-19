#pragma once
#include "Account.h"
#include "Employee.h"
#include "Check.h"
#include "BasicVector.hpp"

class Bank {
private:
	char* name = nullptr;
	BasicVector<Account> accounts;
	BasicVector<Employee> employees;
	BasicVector<Check> checks;

	void moveFrom(Bank&& other);
	void copyFrom(const Bank& other);
	void free();

public:
	Bank();
	Bank(const char* name);
	Bank(const Bank& other);
	Bank(Bank&& other) noexcept;

	Bank& operator=(Bank&& other) noexcept;
	Bank& operator=(const Bank& other);

	~Bank();

	const char* get_bank_name() const;
	Account* find_account(const char* account_number) const;
	void open_account(const User& client);
	void close_account(const char* account_number);

};