#include "BankRepository.h"
#include <iostream>

BankRepository::BankRepository() = default;

BankRepository::BankRepository(const BankRepository& bank_repo) {

}

Bank* BankRepository::find_bank(const char* name) const {
	for (size_t i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == name) {
			return &banks[i];
		}
	}
	return nullptr;
}

void BankRepository::add_bank(Bank& bank) {
	
	banks.push(bank);
}

BankRepository::~BankRepository() = default;