#pragma once
#include "User.h"
#include "Task.h"
#include "BasicVector.hpp"

class Employee : public User {
private:
	BasicVector<Task> tasks;
	MyString bank_name;

public:
	Employee();
	Employee(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password, const MyString& bank);
	
	void help() const override;

	virtual ~Employee();
};