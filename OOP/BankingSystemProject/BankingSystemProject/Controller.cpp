#include "Controller.h"

Controller::Controller() = default;

// Done
bool Controller::bank_exists(const MyString& bank_name) const {

	for (unsigned i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == bank_name) {
			return true;
		}
	}
	return false;
}
// Done
bool Controller::is_logged_in() const {
	return current_user != nullptr;
}
// Done
bool Controller::has_role(UserRole role) const {
	return current_user && current_user->get_role() == role;
}
// Done
Bank& Controller::find_bank(const MyString& bank_name) const {
	for (unsigned i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == bank_name) {
			return banks[i];
		}
	}
	throw new std::runtime_error(BANK_NOT_FOUND);
}
// Done
User* Controller::find_user_by_egn(const MyString& egn) const {
	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i]->get_egn() == egn) {
			return users[i];
		}
	}
	return nullptr;
}


// Done
void Controller::free() {
	delete current_user;
	current_user = nullptr;
}
// Done
bool Controller::exit() {
	if (current_user == nullptr) {
		return true;
	}
	free();
	return false;
}

// Done
void Controller::create_bank(const MyString& bank_name) {
	if (bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_EXISTS);
	}
	if (is_logged_in()) {
		throw std::runtime_error(USER_LOGGED_IN);
	}

	Bank bank(bank_name);
	banks.push(bank);
}
// Done
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
			throw std::invalid_argument(BANK_NOT_FOUND);
		}
		new_user = new Employee(name, egn.c_str(), age, password, bank);

	}
	else if (role == "ThirdPartyEmployee") {
		new_user = new ThirdPartyEmployee(name, egn.c_str(), age, password);
	}
	else {
		throw std::invalid_argument(INVALID_ROLE);
	}

	users.push(new_user);
}
// Done
void Controller::who_am_i() const {

	if (!is_logged_in()) {

		throw std::runtime_error(NO_LOGGED_USER);
	}
	current_user->whoami();
}
// Done
void Controller::help() const {
	if (!is_logged_in()) {

		throw std::runtime_error(NO_LOGGED_USER);
	}
	current_user->help();
}
// Done
void Controller::login(const MyString& name, const MyString& password) {

	if (is_logged_in()) {
		throw std::runtime_error(USER_LOGGED_IN);
	}

	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i]->get_name() == name) {
			if (!users[i]->check_password(password)) {
				throw std::invalid_argument(INVALID_PASSWORD);
			}
			current_user = users[i];
		}
		else {
			throw std::runtime_error(UNSUCCESSFUL_LOGIN);
		}
	}
}
// Done
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
// Done ?
void Controller::open(const MyString& bank_name) {

	MyString task_desc = current_user->get_name() + " wants to create an account.";

	Bank bank = find_bank(bank_name); // throws error if bank not found!
	Task new_task(task_desc, Type::Open, bank.get_task_index(), current_user);
	bank.assign_task(new_task);
}
// Done ?
void Controller::close(const MyString& bank_name, const MyString& account_number) {

	MyString task_desc = current_user->get_name() + " wants to close account with id " + account_number + ".";

	Bank bank = find_bank(bank_name);
	Task new_task(task_desc, Type::Close, bank.get_task_index(), current_user);
	bank.assign_task(new_task);
}
// Done ?
void Controller::redeem(const MyString& bank_name, const MyString& account_number, const char* code) {
	Bank bank = find_bank(bank_name);
	Client* current = dynamic_cast<Client*>(current_user);

	Account account = current->find_account(account_number.c_str());
	if (account.get_bank_name() != bank.get_bank_name()) {
		throw std::invalid_argument(INVALID_DATA);
	}

	current->redeem_check(code, account);
}
// Done ?
void Controller::change(const MyString& new_bank_name, const MyString& current_bank_name, const MyString& account_number) {
	bool new_bank_exists = bank_exists(new_bank_name);
	bool current_bank_exists = bank_exists(current_bank_name);

	if (new_bank_exists && current_bank_exists) {
		MyString task_desc = current_user->get_name() + " wants to join " + new_bank_name + ".";

		Bank bank = find_bank(current_bank_name);

		Task new_task(task_desc, Type::Change, bank.get_task_index(), current_user, new_bank_name);
		bank.assign_task(new_task);
	}

}
// Done
void Controller::list(const MyString& bank_name) const {
	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}

	Client* current = dynamic_cast<Client*>(current_user);
	BasicVector<Account> accounts = current->get_accounts(bank_name);
	if (accounts.size() == 0) {
		std::cout << NO_ACCOUNTS << std::endl;
	}
	else {
		for (unsigned i = 0; i < accounts.size(); i++)
		{
			accounts[i].print();
		}
	}
}
// Done
void Controller::messages() {
	Client* current = dynamic_cast<Client*>(current_user);
	if (current->get_messages_count() == 0) {
		std::cout << EMPTY_INBOX << std::endl;
	}
	else {
		for (unsigned i = 0; i < current->get_messages_count(); i++)
		{
			std::cout << "[" << i + 1 << "] - " << current->get_message_at_index(i) << std::endl;
		}
	}
}
// Done?
void Controller::send_check(double sum, const MyString& bank_name, const MyString& egn) {
	User* egn_user = find_user_by_egn(egn);
	if (egn_user->get_role() != UserRole::client) {
		throw std::invalid_argument(USER_IS_NOT_CLIENT);
	}
	Client* egn_client = dynamic_cast<Client*>(egn_user);
	if (!egn_client->has_accounts_in_bank(bank_name)) {
		throw std::invalid_argument(USER_IS_NOT_CLIENT);
	}

	Check check(sum, bank_name, egn.c_str());
	egn_client->receive_check(check);
	egn_client->receive_message("You have a check assigned to you by " + current_user->get_name() + ". Your verification code is: " + check.get_code());
}
// Done
void Controller::tasks() const {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);
	current->tasks();
}
// Done
void Controller::view(unsigned id) const {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);
	Task task = current->find_task_by_id(id);
	task.print();
}

void Controller::approve(unsigned id) {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);

	Task task = current->find_task_by_id(id);
	User* client_user = find_user_by_egn(task.get_user_egn());

	Client* client = dynamic_cast<Client*>(client_user);


	switch (task.get_task_type())
	{
	case Open:
		// Call OpenAccount() logic
	case Close:
		// Call CloseAccount() logic
	case Change:
		// assume data is validated beforehand
		// Call Change logic
	default:
		break;
	}
	//.delete_at(index);
}

void Controller::disapprove(unsigned id, const MyString& message) {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);
	Task task = current->find_task_by_id(id);

	MyString final_message = "Your " + task.convert_type_to_string() + "request was not approved. Reason: " + message;

	User* client_user = find_user_by_egn(task.get_user_egn());
	Client* client = dynamic_cast<Client*>(client_user);

	client->receive_message(final_message);

	current->disapprove(id);
}


Controller::~Controller() {
	free();
}