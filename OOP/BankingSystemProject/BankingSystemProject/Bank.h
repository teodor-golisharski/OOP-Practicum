#pragma once
#include "Account.h"
#include "Employee.h"
#include "Check.h"
#include "Client.h"
#include "BasicVector.hpp"

class Bank {
private:
	char* name = nullptr;
	BasicVector<Account> accounts;

	void moveFrom(Bank&& other);
	void copyFrom(const Bank& other);
	void free();

	unsigned find_account(const char* account_number) const;
public:
	Bank();
	Bank(const char* name);
	Bank(const Bank& other);
	Bank(Bank&& other) noexcept;

	Bank& operator=(Bank&& other) noexcept;
	Bank& operator=(const Bank& other);

	~Bank();

	const char* get_bank_name() const;
	void open_account(Client& client);
	void close_account(Client& client, const char* account_number);

};