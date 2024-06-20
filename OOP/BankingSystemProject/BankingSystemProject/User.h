#pragma once
#include "GlobalConstants.h"
#include "MyString.hpp"

enum UserRole { DEF = 0, client = 1, employee = 2, thirdPartyEmployee = 3 };

class User {
private:
	MyString name;
	char egn[EGN_LENGTH + 1];
	unsigned age;
	MyString password;
	UserRole role = UserRole::DEF;


public:
	User();
	User(const MyString name, const char egn[EGN_LENGTH], unsigned age, const MyString password, UserRole role);

	void whoami() const;
	virtual void help() const = 0;

	const MyString get_name() const;
	const MyString get_egn() const;
	unsigned get_age() const;
	UserRole get_role() const;
	void update_age();
	bool check_password(const MyString& pass) const;

	virtual ~User();
};