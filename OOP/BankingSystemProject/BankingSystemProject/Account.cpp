#include "Account.h"

Account::Account() = default;

Account::Account(unsigned number, double balance)
	: account_number(number), balance(balance)
{}

unsigned Account::get_account_number() const {
	return this->account_number;
}

double Account::get_balance() const {
	return this->balance;
}

Account::~Account() = default;