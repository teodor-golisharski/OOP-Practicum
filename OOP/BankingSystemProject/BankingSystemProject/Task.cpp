#include "Task.h"
#include "ErrorMessages.hpp"
#include <iostream>
#include "User.h"


Task::Task() = default;

Task::Task(const MyString& name, const Type& task_type, unsigned id, const User* user, const MyString& new_bank) : Task(name, task_type, id, user) {
	this->new_bank = new_bank;
}

Task::Task(const MyString& name, const Type& task_type, unsigned id, const User* user) {

	if (name == "")
		throw std::invalid_argument(EMPTY_FIELD);
	this->name = name;

	this->task_type = task_type;

	this->id = id;

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
		std::cout << "Bank: " << new_bank << std::endl;
	}
}

const MyString& Task::convert_type_to_string() const {
	switch (task_type)
	{
	case Open:
		return "Open";
	case Close:
		return "Close";
	case Change:
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