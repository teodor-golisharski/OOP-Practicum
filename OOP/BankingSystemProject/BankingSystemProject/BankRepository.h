#pragma once
#include "Bank.h"
#include "BasicVector.hpp"

class BankRepository {
private:
	BasicVector<Bank> banks;

public:
	BankRepository();
	BankRepository(const BankRepository& bank_repo);

	Bank* find_bank(const char* bank_name) const;
	void add_bank(Bank& bank);


	~BankRepository();
};