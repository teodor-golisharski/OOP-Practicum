#pragma once

#include "GlobalConstants.h"
#include "MyString.hpp"

class Account final {
private:
	char account_number[ACCOUNT_NUMBER_LENGTH + 1];
	MyString bank_name;
	double balance;

	char generate_random_number(unsigned int& seed);

public:
	Account();
	Account(MyString bank_name);

	const char* get_account_number() const;
	const double get_balance() const;
	const MyString get_bank_name() const;
};