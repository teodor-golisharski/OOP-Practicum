#include "Bank.h"
#include "ErrorMessages.hpp"
#include <iostream>

Bank::Bank() = default;
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
	return -1;
}
const char* Bank::open_account(Client& client, double sum) {
	Account account(this->name);
	account.deposit(sum);

	client.add_account(account);
	this->accounts.push(account);

	return account.get_account_number();
}
void Bank::close_account(Client& client, const char* account_number) {
	unsigned index_from_bank = find_account(account_number);
	unsigned index_from_client = client.find_account_index(account_number);
	
	if (index_from_bank == -1 || index_from_client == -1) {
		throw std::invalid_argument(ACCOUNT_NOT_FOUND);
	}
	this->accounts.delete_at(index_from_bank);
	client.accounts.delete_at(index_from_client);
}

void Bank::delete_task(unsigned id, Employee& employee) {
	for (size_t i = 0; i < employee.tasks_pending.size(); i++)
	{
		if (employee.tasks_pending[i].get_task_id() == id) {
			employee.tasks_pending.delete_at(i);
		}
	}
}
void Bank::assign_task(Task& new_task) {
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
unsigned Bank::get_task_index() {
	return ++last_task_index;
}

unsigned Bank::get_employees_count() const {
	return employees.size();
}
Employee& Bank::get_employee(const MyString& egn) const {
	for (size_t i = 0; i < employees.size(); i++)
	{
		if (employees[i].get_egn() == egn) {
			return employees[i];
		}
	}
}
void Bank::add_employee(const Employee& employee) {
	employees.push(employee);
}
