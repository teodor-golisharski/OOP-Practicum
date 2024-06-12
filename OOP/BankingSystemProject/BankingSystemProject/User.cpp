#include<iostream>
#include "User.h"

void User::free() {
	delete[] name;
	delete[] password;
}
void User::copyFrom(const User& other) {
	set_name(other.name);

	if (!egn || strlen(egn) != EGN_LENGTH) {
		delete[] this->name;
		throw std::invalid_argument("Egn must be exactly 10 digits!");
	}
	strcpy_s(this->egn, EGN_LENGTH + 1, egn);

	if (age < 14) {
		delete[] this->name;
		throw std::invalid_argument("Minimum age is 14!");
	}
	this->age = age;

	if (!password) {
		delete[] this->name;
		throw std::invalid_argument("Password cannot be null!");
	}
	if (strlen(password) > PASSWORD_MAX_LENGTH) {
		delete[] this->name;
		throw std::invalid_argument("Password's maxiumum length is 128 symbols!");
	}
	size_t size_pass = strlen(password) + 1;
	this->password = new char[size_pass];
	strcpy_s(this->password, size_pass, password);
}
void User::moveFrom(User&& other) {
	this->name = other.name;
	other.name = nullptr;

	this->age = other.age;
	other.age = 0;

	for (size_t i = 0; i < EGN_LENGTH; i++)
	{
		this->egn[i] = other.egn[i];
		other.egn[i] = '\0';
	}

	this->password = other.password;
	other.password = nullptr;
}

User::User() = default;
User::~User() {
	free();
}

User::User(const char* name, const char* egn, unsigned age, const char* password) {

	set_name(name);

	if (!egn || strlen(egn) != EGN_LENGTH) {
		delete[] this->name;
		throw std::invalid_argument("Egn must be exactly 10 digits!");
	}
	strcpy_s(this->egn, EGN_LENGTH + 1, egn);

	if (age < 14) {
		delete[] this->name;
		throw std::invalid_argument("Minimum age is 14!");
	}
	this->age = age;

	if (!password) {
		delete[] this->name;
		throw std::invalid_argument("Password cannot be null!");
	}
	if (strlen(password) > PASSWORD_MAX_LENGTH) {
		delete[] this->name;
		throw std::invalid_argument("Password's maxiumum length is 128 symbols!");
	}
	size_t size_pass = strlen(password) + 1;
	this->password = new char[size_pass];
	strcpy_s(this->password, size_pass, password);
}
User::User(const User& other) {
	copyFrom(other);
}
User::User(User&& other) noexcept {
	moveFrom(std::move(other));
}
User& User::operator=(const User& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
User& User::operator=(User&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void User::exit(User* currentUser) {
	return;
}

void User::whoami() const {
	std::cout << "You are " << name << "!" << std::endl;
}

const char* User::get_name() const {
	return this->name;
}
const char* User::get_egn() const {
	return this->egn;
}
unsigned User::get_age() const {
	return this->age;
}

void User::set_name(const char* name) {
	if (!name) {
		throw std::invalid_argument("Name cannot be null!");
	}
	size_t size_name = strlen(name) + 1;
	this->name = new char[size_name];
	strcpy_s(this->name, size_name, name);
}