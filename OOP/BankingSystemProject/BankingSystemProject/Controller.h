#pragma once
#include "Bank.h"
#include "User.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"
#include "BasicVector.hpp"
#include "MyString.hpp"
#include "ErrorMessages.h"

class Controller final{
private:
	BasicVector<Bank> banks;
	BasicVector<User*> users;
	User* current_user = nullptr;

	void free();
	
	bool bank_exists(const MyString& bank_name) const;
	Bank& find_bank(const MyString& bank_name) const;

public:
	Controller();

	bool is_logged_in() const;
	bool has_role(UserRole role) const;

	bool exit();
	void create_bank(const MyString& bank_name);
	void signup(const MyString& name, const MyString& egn, const MyString& role, const MyString& password, unsigned age);
	void who_am_i() const;
	void help() const;
	void login(const MyString& name, const MyString& password);

	void check_avl(const MyString& bank_name, const MyString& account_number) const;
	void open(const MyString& bank_name);

	~Controller();
};