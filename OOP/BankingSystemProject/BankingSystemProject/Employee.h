#pragma once
#include "User.h"
#include "Task.h"
#include "BasicVector.hpp"

class Employee : public User {
private:
	BasicVector<Task> tasks_pending;
	MyString bank_name;

	int find_task(unsigned task_id) const;
public:
	Employee();
	Employee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password, const MyString& bank);
	
	void help() const override;

	void tasks() const;
	void view(unsigned task_id) const;
	void approve(unsigned task_id);
	void disapprove(unsigned task_id);

	const int get_task_count() const;
	void add_task(Task new_task);

	Task& find_task_by_id(unsigned id) const;

	virtual ~Employee();
};