#include "Task.h"
#include <iostream>

void Task::copyFrom(const Task& other) {

	size_t size = strlen(other.name) + 1;
	this->name = new char[size];
	strcpy_s(name, size, other.name);

	this->task_type = other.task_type;

	this->id = other.id;
}

void Task::moveFrom(Task&& other) {

	name = other.name;
	other.name = nullptr;

	task_type = other.task_type;

	id = other.id;
	other.id = 0;
}

void Task::free() {
	delete[] name;
	name = nullptr;
}

Task::Task() = default;

Task::Task(char* name, type task_type, unsigned id) {

	if (!name) {
		throw std::invalid_argument("Task name cannot be empty!");
	}
	size_t size = strlen(name) + 1;
	strcpy_s(this->name, size, name);

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

Task::Task(const Task& other) {
	copyFrom(other);
}

Task::Task(Task&& other) noexcept {
	moveFrom(std::move(other));
}

Task& Task::operator=(const Task& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Task& Task::operator=(Task&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

const char* Task::get_task_name() const {
	return this->name;
}
const char* Task::get_task_type() const {
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

Task::~Task() {
	free();
}