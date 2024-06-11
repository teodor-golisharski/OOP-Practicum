#pragma once

class Account final {
private:
	unsigned account_number;
	double balance;
public:
	Account();
	Account(unsigned number, double balance);
	
	unsigned get_account_number() const;
	double get_balance() const;
	~Account();
};