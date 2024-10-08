#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee() = default;

ThirdPartyEmployee::ThirdPartyEmployee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password)
	: User(name, egn, age, password, UserRole::thirdPartyEmployee) { }

void ThirdPartyEmployee::help() const {
    std::cout << "----------------------------------------------------------------------------\n";
    std::cout << "Third-Party Employee Commands:\n";
    std::cout << " * send_check [sum] [bank_name] [egn] - Send a check\n";
    std::cout << " * exit - Logout\n";
    std::cout << " * whoami - Show current user information\n";
    std::cout << " * help - Show this help menu\n";
    std::cout << "----------------------------------------------------------------------------\n";
}

ThirdPartyEmployee::~ThirdPartyEmployee() = default;
