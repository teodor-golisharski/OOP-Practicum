#include<iostream>
#include "User.h"

User::User() = default;
User::~User() = default;

User::User(const MyString name, const char egn[EGN_LENGTH], unsigned age, const MyString password, UserRole role) {

	if (name == "")
		throw std::invalid_argument("Name cannot be empty!");
	this->name = name;

	if (!egn || strlen(egn) != EGN_LENGTH)
		throw std::invalid_argument("Egn must be exactly 10 digits!");
	strcpy_s(this->egn, EGN_LENGTH + 1, egn);

	if (age < 14)
		throw std::invalid_argument("Minimum age is 14!");
	this->age = age;

	if (password == "")
		throw std::invalid_argument("Password cannot be null!");
	if (password.length() > PASSWORD_MAX_LENGTH)
		throw std::invalid_argument("Password's maxiumum length is 128 symbols!");
	this->password = password;

	this->role = role;
}

void User::whoami() const {
	std::cout << "You are " << name << "!" << std::endl;
}

const MyString User::get_name() const {
	return this->name;
}

const MyString User::get_egn() const {
	return this->egn;
}

unsigned User::get_age() const {
	return this->age;
}

void User::update_age() {
	this->age++;
}

UserRole User::get_role() const{
	return this->role;
}