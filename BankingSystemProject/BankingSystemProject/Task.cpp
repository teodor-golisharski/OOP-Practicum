#include "Task.h"
#include "ErrorMessages.hpp"
#include <iostream>
#include "User.h"


Task::Task() : name(""), task_type(def), id(0), user_name(""), user_egn(""), user_age(0), new_bank(""), account_number(""), validated(false) {}
Task::Task(const MyString& name, const Type& task_type, unsigned id, const User* user, const MyString& new_bank, const MyString& account_number) : Task(name, task_type, id, user, account_number) {
	this->new_bank = new_bank;
}
Task::Task(const MyString& name, const Type& task_type, unsigned id, const User* user, const MyString& account_number) : Task(name, task_type, id, user) {
	this->account_number = account_number;
}
Task::Task(const MyString& name, const Type& task_type, unsigned id, const User* user)
	: name(name), task_type(task_type), id(id), new_bank(""), account_number(""), validated(false) {
	if (name == "") throw std::invalid_argument(EMPTY_FIELD);

	if (user == nullptr) {
		throw std::runtime_error(NO_LOGGED_USER);
	}
	this->user_name = user->get_name();
	this->user_egn = user->get_egn();
	this->user_age = user->get_age();
}

const MyString& Task::get_task_name() const {
	return this->name;
}
Type Task::get_task_type() const {
	return this->task_type;
}
const unsigned int Task::get_task_id() const {
	return this->id;
}

void Task::print() const {
	std::cout << convert_type_to_string() + " request from:" << std::endl;
	std::cout << "Name: " << user_name << std::endl;
	std::cout << "EGN: " << user_egn << std::endl;
	std::cout << "Age: " << user_age << std::endl;
	if (new_bank.length() > 0) {
		std::cout << "New bank: " << new_bank << std::endl;
	}
}

const MyString Task::convert_type_to_string() const {
	switch (task_type)
	{
	case Type::Open:
		return "Open";
	case Type::Close:
		return "Close";
	case Type::Change:
		return "Change";
	default:
		return "def";
	}
}

const MyString& Task::get_user_name() const {
	return this->user_name;
}
const MyString& Task::get_user_egn() const {
	return this->user_egn;
}
unsigned Task::get_user_age() const {
	return this->user_age;
}
const MyString& Task::get_bank_name() const {
	return this->new_bank;
}
const MyString& Task::get_account_number() const {
	return this->account_number;
}

bool Task::get_validation_status() const {
	return this->validated;
}
void Task::validate_task() {
	this->validated = true;
}