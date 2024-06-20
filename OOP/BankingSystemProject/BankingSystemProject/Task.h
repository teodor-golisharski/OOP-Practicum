#pragma once

#include "MyString.hpp"
enum Type { Open, Close, Change };

class Task final {
private:
	MyString name;
	Type task_type;
	unsigned id;

public:
	Task();
	Task(MyString name, Type task_type, unsigned id);

	const MyString get_task_name() const;
	const MyString get_task_type() const;
	const unsigned int get_task_id() const;
};