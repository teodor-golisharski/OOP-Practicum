#pragma once
#include "GlobalConstants.h"

class Account final {
private:
	char account_number[ACCOUNT_NUMBER_LENGTH + 1];
	double balance;
	char* bank_name;
public:
	Account();
	Account(char number[ACCOUNT_NUMBER_LENGTH + 1], double balance);

	const char* get_account_number() const;
	double get_balance() const;
	~Account();
};