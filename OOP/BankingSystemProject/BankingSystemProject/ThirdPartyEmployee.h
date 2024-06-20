#pragma once
#include "User.h"

class ThirdPartyEmployee : public User {
public:
	ThirdPartyEmployee();
	ThirdPartyEmployee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password);
	
	void send_check(double sum, const MyString& bank_name, const char egn[EGN_LENGTH]);
	
	void help() const override;

	virtual ~ThirdPartyEmployee();
};