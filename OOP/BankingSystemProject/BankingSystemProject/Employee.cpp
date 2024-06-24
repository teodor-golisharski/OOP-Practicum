#include "Employee.h"
#include "Bank.h"
#include "ErrorMessages.hpp"

int Employee::find_task(unsigned task_id) const {
	for (size_t i = 0; i < this->get_task_count(); i++) {
		if (tasks_pending[i].get_task_id() == task_id)
			return i;
	}
	return -1;
}

Employee::Employee() = default;
Employee::~Employee() = default;

Employee::Employee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password, const MyString& bank) :
	User(name, egn, age, password, UserRole::employee) {
	bank_name = bank;
}

void Employee::help() const {
	std::cout << "----------------------------------------------------------------------------\n";
	std::cout << "Employee commands:\n";
	std::cout << " * tasks - Show assigned tasks\n";
	std::cout << " * view [task_id] - Show all details about specific task\n";
	std::cout << " * approve [task_id] - Finishes a task and approves the request\n";
	std::cout << " * disapprove [task_id] [message] - Finishes a task and disapproves the request\n";
	std::cout << " * validate [task_id] - Sends a request to the old bank to validate data. Works only for Change requests\n";
	std::cout << "----------------------------------------------------------------------------\n";
}

void Employee::tasks() const {
	if (this->get_task_count() == 0) {
		std::cout << NO_TASKS_AVAILABLE << std::endl;
	}
	else {
		for (unsigned i = 0; i < this->get_task_count(); i++) {
			std::cout << tasks_pending[i].get_task_name() << " " << tasks_pending[i].get_task_id()
				<< " " << tasks_pending[i].get_task_type() << std::endl;
		}
	}
}

void Employee::view(unsigned task_id) const {
	int index = find_task(task_id);
	if (index >= 0)
		std::cout << "Task Name: " << tasks_pending[index].get_task_name()
		<< " Task Type: " << tasks_pending[index].get_task_type() << std::endl;
	else
		std::cout << "Employee " << this->get_name() << " has no pending task with this id." << std::endl;
}

// useless
void Employee::approve(unsigned task_id) {

	int index = find_task(task_id);
	if (index == -1)
		throw std::invalid_argument(TASK_NOT_FOUND);

	switch (tasks_pending[index].get_task_type())
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
	tasks_pending.delete_at(index);
}

void Employee::disapprove(unsigned task_id) {

	int index = find_task(task_id);
	if (index == -1)
		throw std::invalid_argument(TASK_NOT_FOUND);

	std::cout << "Task: " << tasks_pending[index].get_task_name()
		<< " " << tasks_pending[index].get_task_id() << " has not been approved!" << std::endl;
	tasks_pending.delete_at(index);
}

const int Employee::get_task_count() const {
	return tasks_pending.size();
}

void Employee::add_task(Task new_task) {
	this->tasks_pending.push(new_task);
}

Task& Employee::find_task_by_id(unsigned id) const {
	if (find_task(id) == -1) {
		throw std::invalid_argument(TASK_NOT_FOUND);
	}
	return tasks_pending[find_task(id)];

}
