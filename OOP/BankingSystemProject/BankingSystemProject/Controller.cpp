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
Bank& Controller::find_bank(const MyString& bank_name) const {
	for (size_t i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == bank_name) {
			return banks[i];
		}
	}
	throw new std::runtime_error(BANK_NOT_FOUND);
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
			throw new std::invalid_argument(BANK_NOT_FOUND);
		}
		new_user = new Employee(name, egn.c_str(), age, password, bank);

	}
	else if (role == "ThirdPartyEmployee") {
		new_user = new ThirdPartyEmployee(name, egn.c_str(), age, password);
	}
	else {
		throw new std::invalid_argument(INVALID_ROLE);
	}

	users.push(new_user);
}
void Controller::who_am_i() const {

	if (is_logged_in()) {

		current_user->whoami();
	}
	throw new std::runtime_error(NO_LOGGED_USER);

}
void Controller::help() const {
	if (is_logged_in()) {

		current_user->help();
	}
	throw new std::runtime_error(NO_LOGGED_USER);

}
void Controller::login(const MyString& name, const MyString& password) {

	if (is_logged_in()) {
		throw new std::runtime_error(USER_LOGGED_IN);
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

void Controller::check_avl(const MyString& bank_name, const MyString& account_number) const {
	
	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}
	Client* current = dynamic_cast<Client*>(current_user);
	double balance = current->find_account(account_number
		.c_str())
		.get_balance();

	std::cout << balance << "$" << std::endl;
}
void Controller::open(const MyString& bank_name) {
	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}
	MyString task_desc = current_user->get_name() + " wants to create an account.";
	//Task new_task(task_desc, Type::Open, find_bank(bank_name));
}

Controller::~Controller() {
	free();
}