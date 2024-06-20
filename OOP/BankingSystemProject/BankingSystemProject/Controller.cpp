#include "Controller.h"

Controller::Controller() = default;

bool Controller::bank_exists(const MyString& bank_name) const {

	for (size_t i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == bank_name) {
			return true;
		}
	}
	return false;
}
bool Controller::is_logged_in() const {
	return current_user != nullptr;
}
bool Controller::has_role(UserRole role) const {
	return current_user && current_user->get_role() == role;
}

void Controller::free() {
	delete current_user;
	current_user = nullptr;
}
bool Controller::exit() {
	if (current_user == nullptr) {
		return true;
	}
	free();
	return false;
}

// TO DO:
UserRole Controller::user_factory(const MyString& role) {
	if (role == "Client") {
		return UserRole::client;
	}
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Controller::create_bank(const MyString& bank_name) {
	Bank bank(bank_name);
	banks.push(bank);
	std::cout << banks.size();
}
void Controller::signup(const MyString& name, const MyString& egn, const MyString& role, const MyString& password, unsigned age) {

	User* new_user;

	if (role == "Client") {
		new_user = new Client(name, egn.c_str(), age, password);
	}
	else if (role == "Employee") {
		MyString bank;
		std::cout << "Bank associated: ";
		std::cin >> bank;

		if (!bank_exists(bank)) {
			throw new std::invalid_argument("Bank not found!");
		}
		new_user = new Employee(name, egn.c_str(), age, password, bank);

	}
	else if (role == "ThirdPartyEmployee") {
		new_user = new ThirdPartyEmployee(name, egn.c_str(), age, password);
	}
	else {
		throw new std::invalid_argument("Invalid role specified!");
	}

	users.push(new_user);
}
void Controller::who_am_i() const {

	if (is_logged_in()) {

		current_user->whoami();
	}
	throw new std::runtime_error("No user is currently logged in!");

}
void Controller::help() const {
	if (is_logged_in()) {

		current_user->help();
	}
	throw new std::runtime_error("No user is currently logged in!");

}
void Controller::login(const MyString& name, const MyString& password) {

	if (is_logged_in()) {
		throw new std::runtime_error("User is already logged in!");
	}

	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->get_name() == name) {
			if (users[i]->check_password(password)) {
				current_user = users[i];
			}
		}
	}
}


Controller::~Controller() {
	free();
}