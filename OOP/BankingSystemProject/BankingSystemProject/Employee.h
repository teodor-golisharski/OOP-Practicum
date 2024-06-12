#pragma once
#include "User.h"
#include "Task.h"

class Employee : public User {
private:
	Task* tasks;
};