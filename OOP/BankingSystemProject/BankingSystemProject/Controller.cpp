#include "Controller.h"

Controller::Controller() = default;

void Controller::create_bank(const MyString& bank_name) {
	Bank bank(bank_name);
	banks.push(bank);
	std::cout << banks.size();
}

Controller::~Controller() {
	delete current_user;
	current_user = nullptr;
}