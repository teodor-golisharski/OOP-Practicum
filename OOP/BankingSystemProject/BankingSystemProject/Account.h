#pragma once

#include "GlobalConstants.h"

class Account final {
private:
	char account_number[ACCOUNT_NUMBER_LENGTH + 1];
	char* bank_name;
	double balance;

	char generate_random_number(unsigned int& seed);

	void copyFrom(const Account& other);
	void moveFrom(Account&& other);
	void free();

public:
	Account();
	Account(char* bank_name);

	Account(const Account& other);
	Account(Account&& other) noexcept;

	Account& operator=(const Account& other);
	Account& operator=(Account&& other) noexcept;

	const char* get_account_number() const;
	const double get_balance() const;
	void set_balance(double new_balance);
	const char* get_bank_name() const;

	~Account();
};