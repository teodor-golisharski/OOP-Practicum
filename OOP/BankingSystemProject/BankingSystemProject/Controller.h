#pragma once
#include "Bank.h"
#include "User.h"
#include "BasicVector.hpp"
#include "MyString.hpp"

class Controller final{
private:
	BasicVector<Bank> banks;
	BasicVector<User*> users;
	User* current_user = nullptr;

public:
	Controller();

	//Bank& find_bank(const char* bank_name) const;
	void create_bank(const MyString& bank_name);
	
	//void exit();

	
	~Controller();
};