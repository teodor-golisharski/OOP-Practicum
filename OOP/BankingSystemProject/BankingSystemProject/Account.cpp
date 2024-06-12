#include "Account.h"
#include <iostream>

Account::Account() = default;

Account::Account(char number[ACCOUNT_NUMBER_LENGTH + 1], double balance)
	: balance(balance)
{
	strcpy_s(this->account_number, ACCOUNT_NUMBER_LENGTH + 1, number);
}

const char* Account::get_account_number() const {
	return this->account_number;
}

double Account::get_balance() const {
	return this->balance;
}

Account::~Account() = default;