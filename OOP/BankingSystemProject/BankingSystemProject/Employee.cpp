#include "Employee.h"

Employee::Employee() = default;
Employee::~Employee() = default;

Employee::Employee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password, const MyString& bank) :
	User(name, egn, age, password, UserRole::employee) {
	bank_name = bank;
}

void Employee::help() const {
	std::cout << std::endl;
}

