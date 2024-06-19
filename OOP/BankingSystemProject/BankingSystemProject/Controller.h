#pragma once
#include "Bank.h"
#include "User.h"
#include "BasicVector.hpp"


class Controller final{
private:
	BasicVector<Bank> banks;
	BasicVector<User> users;
	User* current_user = nullptr;

public:
	/*Controller();

	Bank& find_bank(const char* bank_name) const;
	void add_bank(const Bank& bank);
	
	void exit();

	
	~Controller();*/
};