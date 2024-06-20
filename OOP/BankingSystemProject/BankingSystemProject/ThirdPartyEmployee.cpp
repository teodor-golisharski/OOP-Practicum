#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee() = default;

ThirdPartyEmployee::ThirdPartyEmployee(const char* name, const char* egn, unsigned age, const char* password) : User(name, egn, age, password, UserRole::thirdPartyEmployee) {
	
}

ThirdPartyEmployee::~ThirdPartyEmployee() = default;
