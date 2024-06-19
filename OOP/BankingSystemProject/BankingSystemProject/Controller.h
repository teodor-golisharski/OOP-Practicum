#pragma once
#include "BankRepository.h"
#include "User.h"

class Controller {
private:
	BankRepository banks;
	User* users;
	User* current_user;

public:
	Controller();

	Bank& find_bank_by_name(const char* bank_name) const;
	void add_bank(const Bank& bank);
	
	void exit();

	
	~Controller();
};