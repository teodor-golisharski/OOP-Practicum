#pragma once

#include "MyString.hpp"

class Task final {
private:
	MyString name;
	enum Type { Open, Close, Change };
	Type task_type;
	unsigned id;

public:
	Task();
	Task(MyString name, Type task_type, unsigned id);

	const MyString get_task_name() const;
	const MyString get_task_type() const;
	const unsigned int get_task_id() const;
};