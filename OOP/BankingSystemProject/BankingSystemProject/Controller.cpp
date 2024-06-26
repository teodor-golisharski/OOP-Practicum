#include "Controller.h"

Controller::Controller() : current_user(nullptr) {}

bool Controller::bank_exists(const MyString& bank_name) const {

	for (unsigned i = 0; i < banks.size(); i++)
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

	for (unsigned i = 0; i < banks.size(); i++)
	{
		if (banks[i].get_bank_name() == bank_name) {
			return banks[i];
		}
	}
	throw new std::runtime_error(BANK_NOT_FOUND);
}
User* Controller::find_user_by_egn(const MyString& egn) const {
	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i]->get_egn() == egn) {
			return users[i];
		}
	}
	return nullptr;
}

void Controller::free() {
	users.clear();
	banks.clear();

	delete current_user;
	current_user = nullptr;
}
bool Controller::exit() {
	if (current_user == nullptr) {
		free();
		return true;
	}
	current_user = nullptr;
	return false;
}

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
		Bank& temp = find_bank(bank);
		Employee* casted = dynamic_cast<Employee*>(new_user);

		temp.add_employee(*casted);
	}
	else if (role == "Third-party") {
		new_user = new ThirdPartyEmployee(name, egn.c_str(), age, password);
	}
	else {
		throw std::invalid_argument(INVALID_ROLE);
	}

	users.push(new_user);
}
void Controller::who_am_i() const {

	if (!is_logged_in()) {

		throw std::runtime_error(NO_LOGGED_USER);
	}
	current_user->whoami();
}
void Controller::help() const {
	if (!is_logged_in()) {

		throw std::runtime_error(NO_LOGGED_USER);
	}
	current_user->help();
}
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

			return;
		}
	}
	throw std::runtime_error(UNSUCCESSFUL_LOGIN);
}
void Controller::check_avl(const MyString& bank_name, const MyString& account_number) const {

	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}
	Client* current = dynamic_cast<Client*>(current_user);

	Account& acc = current->find_account(account_number.c_str());
	double balance = acc.get_balance();

	std::cout << balance << "$" << std::endl;
}
void Controller::open(const MyString& bank_name) {

	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}

	Bank& bank = find_bank(bank_name);
	if (bank.get_employees_count() == 0) {
		throw std::runtime_error(BANK_NOT_OPERATING);
	}
	MyString task_desc = current_user->get_name() + " wants to create an account.";

	Task new_task(task_desc, Type::Open, bank.get_task_index(), current_user);
	bank.assign_task(new_task);
}
void Controller::close(const MyString& bank_name, const MyString& account_number) {

	MyString task_desc = current_user->get_name() + " wants to close account with id " + account_number + ".";

	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}

	Bank& bank = find_bank(bank_name);
	if (bank.get_employees_count() == 0) {
		throw std::runtime_error(BANK_NOT_OPERATING);
	}

	Client* cli = dynamic_cast<Client*>(current_user);
	if (cli->find_account_index(account_number.c_str()) == -1) {
		throw std::invalid_argument(ACCOUNT_NOT_FOUND);
	}

	Task new_task(task_desc, Type::Close, bank.get_task_index(), current_user, account_number);
	bank.assign_task(new_task);
}
void Controller::redeem(const MyString& bank_name, const MyString& account_number, const char* code) {

	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}

	Bank bank = find_bank(bank_name);
	Client* current = dynamic_cast<Client*>(current_user);

	if (current->find_account_index(account_number.c_str()) == -1) {
		throw std::invalid_argument(ACCOUNT_NOT_FOUND);
	}
	Account& account = current->find_account(account_number.c_str());
	if (account.get_bank_name() != bank.get_bank_name()) {
		throw std::invalid_argument(INVALID_DATA);
	}

	current->redeem_check(code, account);
	MyString code_string = code;
	current->receive_message("You redeemed a check with code \"" + code_string + "\" to account: " + account_number);
}
void Controller::change(const MyString& new_bank_name, const MyString& current_bank_name, const MyString& account_number) {
	bool new_bank_exists = bank_exists(new_bank_name);
	bool current_bank_exists = bank_exists(current_bank_name);

	if (new_bank_exists && current_bank_exists) {

		Bank& bank = find_bank(current_bank_name);
		if (bank.get_employees_count() == 0) {
			throw std::runtime_error(BANK_NOT_OPERATING);
		}

		Client* cli = dynamic_cast<Client*>(current_user);
		if (cli->find_account_index(account_number.c_str()) != -1) {
			Account& acc = cli->find_account(account_number.c_str());

			if (acc.get_bank_name() != current_bank_name) {
				throw std::invalid_argument(ACCOUNT_NOT_FOUND);
			}
		}
		else {
			throw std::invalid_argument(ACCOUNT_NOT_FOUND);
		}

		MyString task_desc = current_user->get_name() + " wants to join " + new_bank_name + ".";
		Task new_task(task_desc, Type::Change, bank.get_task_index(), current_user, new_bank_name, account_number);
		bank.assign_task(new_task);
	}
	else {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}

}
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

void Controller::send_check(double sum, const MyString& bank_name, const MyString& egn) {

	if (!bank_exists(bank_name)) {
		throw std::invalid_argument(BANK_NOT_FOUND);
	}
	User* egn_user = find_user_by_egn(egn);
	if (egn_user == nullptr) {
		throw std::invalid_argument(USER_NOT_FOUND);
	}

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

void Controller::tasks() const {

	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);

	Bank& bank = find_bank(current->get_bank_name());
	Employee& emp = bank.get_employee(current->get_egn());

	emp.tasks();
}
void Controller::view(unsigned id) const {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);

	Bank& bank = find_bank(current->get_bank_name());
	Employee& emp = bank.get_employee(current->get_egn());

	Task task = emp.find_task_by_id(id);
	task.print();
}
void Controller::approve(unsigned id) {

	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);
	Employee& emp = find_bank(current->get_bank_name()).get_employee(current->get_egn());

	Task& task = emp.find_task_by_id(id);

	User* client_user = find_user_by_egn(task.get_user_egn());
	Client* client = dynamic_cast<Client*>(client_user);

	Bank& bank = find_bank(current->get_bank_name());
	switch (task.get_task_type())
	{
	case Open: {
		MyString account_number = bank.open_account(*client, 0);
		client->receive_message("You opened an account in " + bank.get_bank_name() + "! Your account id is " + account_number.c_str() + ". Approved by: " + current->get_name());
		break;

	}
	case Close: {
		bank.close_account(*client, task.get_account_number().c_str());
		client->receive_message("You closed an account in " + bank.get_bank_name() + " with id " + task.get_account_number() + ". Approved by: " + current->get_name());
		break;
	}
	case Change: {
		if (!task.get_validation_status()) {
			MyString error_message = "Cannot proceed - please make sure " + client->get_name() + " is real user by asking the bank!";
			throw std::runtime_error(error_message.c_str());
		}
		Account& acc = client->find_account(task.get_account_number().c_str());

		if (!bank_exists(acc.get_bank_name())) {
			throw std::runtime_error(BANK_NOT_FOUND);
		}

		Bank& new_bank = find_bank(task.get_bank_name());
		double current_balance = acc.get_balance();
		
		MyString accountNumber = new_bank.open_account(*client, current_balance);
		bank.close_account(*client, task.get_account_number().c_str());
		
		client->transfer_checks(current->get_bank_name(), task.get_bank_name());
		client->receive_message("Your account has been successfully transferred to " + bank.get_bank_name() + " Your new account number is: " + accountNumber + ". Approved by: " + current->get_name());
		break;
	}

	default:
		throw std::runtime_error(INVALID_TASK_TYPE);
	}
	emp.approve(id);
}
void Controller::disapprove(unsigned id, const MyString& message) {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}
	Employee* current = dynamic_cast<Employee*>(current_user);
	Bank& bank = find_bank(current->get_bank_name());
	Employee& emp = bank.get_employee(current->get_egn());

	Task task = emp.find_task_by_id(id);
	if (task.get_task_type() == Type::Change && !task.get_validation_status()) {
		MyString error_message = "Cannot proceed - please make sure " + task.get_user_name() + " is real user by asking the bank!";
		throw std::runtime_error(error_message.c_str());
	}
	MyString final_message = "Your " + task.convert_type_to_string() + " request was not approved by" + current->get_name() + ". Reason:" + message;

	User* client_user = find_user_by_egn(task.get_user_egn());
	Client* client = dynamic_cast<Client*>(client_user);
	client->receive_message(final_message);

	emp.disapprove(id);
}
void Controller::validate(unsigned id) {
	if (!has_role(UserRole::employee)) {
		throw std::runtime_error(NO_ACCESS);
	}

	Employee* current = dynamic_cast<Employee*>(current_user);
	Bank& bank = find_bank(current->get_bank_name());
	Employee& emp = bank.get_employee(current->get_egn());

	Task& task = emp.find_task_by_id(id);

	if (task.get_task_type() != Change) {
		throw std::invalid_argument(VALIDATION_ERROR);
	}

	User* client_user = find_user_by_egn(task.get_user_egn());
	Client* client = dynamic_cast<Client*>(client_user);

	if (client->has_account(task.get_account_number())) {
		task.validate_task();
	}
}

Controller::~Controller() {
	free();
}