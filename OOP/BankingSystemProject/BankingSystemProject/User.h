#pragma once
#include "GlobalConstants.h"

class User {
private:
	char* name;
	char egn[EGN_LENGTH];
	unsigned age;
	char* password;

	void copyFrom(const User& other);
	void moveFrom(User&& other);
	void free();

public:
	User();
	User(const char* name, const char* egn, unsigned age, const char* password);
	User(const User& other);
	User(User&& other) noexcept;

	User& operator=(const User& other);
	User& operator=(User&& other) noexcept;

	void exit(User* currentUser);

	void whoami() const;
	virtual void help() const = 0;

	const char* get_name() const;
	const char* get_egn() const;
	unsigned get_age() const;

	void set_name(const char* name);
	
	virtual ~User();
};