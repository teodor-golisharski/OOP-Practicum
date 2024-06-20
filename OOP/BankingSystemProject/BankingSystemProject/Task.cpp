#include "Task.h"
#include <iostream>

Task::Task() = default;

Task::Task(MyString name, Type task_type, unsigned id) {

	if (name == "")
		throw std::invalid_argument("Task name cannot be empty!");
	this->name = name;

	switch (task_type) {
	case Open:
		this->task_type = Open;
		break;
	case Close:
		this->task_type = Close;
		break;
	case Change:
		this->task_type = Change;
	default:
		throw std::invalid_argument("Task type must be either Open, Close or Change!");
		break;
	}

	this->id = id;
}

const MyString Task::get_task_name() const {
	return this->name;
}
const MyString Task::get_task_type() const {
	switch (this->task_type)
	{
	case Task::Open:
		return "Open";
		break;
	case Task::Close:
		return "Close";
		break;
	case Task::Change:
		return "Change";
		break;
	default:
		throw std::exception("Task has no type");
		break;
	}
}
const unsigned int Task::get_task_id() const {
	return this->id;
}