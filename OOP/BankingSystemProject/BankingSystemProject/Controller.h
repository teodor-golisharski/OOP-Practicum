#pragma once
#include "Bank.h"
#include "User.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"
#include "BasicVector.hpp"
#include "MyString.hpp"
#include "ErrorMessages.hpp"

class Controller final{
private:
	BasicVector<Bank> banks;
	BasicVector<User*> users;
	User* current_user = nullptr;

	void free();
	
	bool bank_exists(const MyString& bank_name) const;
	Bank& find_bank(const MyString& bank_name) const;
	User* find_user_by_egn(const MyString& egn) const;

	
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
	void close(const MyString& bank_name, const MyString& account_number);
	void redeem(const MyString& bank_name, const MyString& account_number, const char* code);
	void change(const MyString& new_bank_name, const MyString& current_bank_name, const MyString& account_number);
	void list(const MyString& bank_name) const;
	void messages();

	void send_check(double sum, const MyString& bank_name, const MyString& egn);

	void tasks() const;
	void view(unsigned id) const;
	void approve(unsigned id);
	void disapprove(unsigned id, const MyString& message);

	~Controller();
};