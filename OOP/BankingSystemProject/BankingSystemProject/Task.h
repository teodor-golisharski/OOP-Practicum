#pragma once
#include "User.h"
#include "MyString.hpp"
enum Type { Open, Close, Change };

class Task final {
private:
	MyString name;
	Type task_type;
	unsigned id = 0;

	MyString user_name;
	MyString user_egn;
	unsigned user_age = 0;
	MyString new_bank;
	MyString account_number;

	bool validated = false;

public:
	Task();
	Task(const MyString& name, const Type& task_type, unsigned id, const User* user);
	Task(const MyString& name, const Type& task_type, unsigned id, const User* user, const MyString& new_bank, const MyString& account_number);

	const MyString& get_task_name() const;
	Type get_task_type() const;
	const unsigned int get_task_id() const;
	void print() const;

	const MyString& get_user_name() const;
	const MyString& get_user_egn() const;
	unsigned get_user_age() const;
	const MyString& get_bank_name() const;
	const MyString& get_account_number() const;
	const MyString& convert_type_to_string() const;
	
	bool get_validation_status() const;
	void validate_task();
};