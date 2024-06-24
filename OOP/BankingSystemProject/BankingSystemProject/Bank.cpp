#include "Bank.h"
#include "ErrorMessages.hpp"
#include <iostream>

Bank::Bank() = default;

unsigned Bank::get_task_index() {
	return ++last_task_index;
}


Bank::Bank(const MyString& name) {
	if (name == "")
		throw std::invalid_argument(EMPTY_FIELD);

	this->name = name;
}

const MyString& Bank::get_bank_name() const {
	return this->name;
}

unsigned Bank::find_account(const char* account_number) const {
	for (unsigned i = 0; i < accounts.size(); i++)
	{
		if (strcmp(accounts[i].get_account_number(), account_number) == 0) {
			return i;
		}
	}
	throw new std::invalid_argument(ACCOUNT_NOT_FOUND);
}

void Bank::assign_task(Task new_task) {
	int min = employees[0].get_task_count();
	int index = 0;
	for (unsigned i = 0; i < employees.size(); i++) {
		if (employees[i].get_task_count() < min) {
			min = employees[i].get_task_count();
			index = i;
		}
	}
	employees[index].add_task(new_task);
}



const MyString& Bank::open_account(Client& client, double sum) {
	Account account(this->name);
	account.deposit(sum);

	client.add_account(account);
	this->accounts.push(account);

	return account.get_account_number();
}

void Bank::close_account(Client& client, const char* account_number) {
	unsigned index = find_account(account_number);
	this->accounts.delete_at(index);

	index = client.find_account_index(account_number);
	client.accounts.delete_at(index);
}

void Bank::delete_task(unsigned id, Employee& employee) {
	for (size_t i = 0; i < employee.tasks_pending.size(); i++)
	{
		if (employee.tasks_pending[i].get_task_id() == id) {
			employee.tasks_pending.delete_at(i);
		}
	}
}

