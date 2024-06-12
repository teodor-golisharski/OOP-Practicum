#pragma once
#include "User.h"

class ThirdPartyEmployee : public User {
public:
	ThirdPartyEmployee();
	ThirdPartyEmployee(const char* name, const char* egn, unsigned age, const char* password);
	

	void send_check(double sum, const char* bank_name, const char egn[EGN_LENGTH]);
	
	virtual ~ThirdPartyEmployee();
};