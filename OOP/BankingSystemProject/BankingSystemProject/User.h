#pragma once

class User {
private:
	char* name;
	char egn[10];
	unsigned age;

public:
	void exit(User* currentUser);

	virtual void whoami() const = 0;
	virtual void help() const = 0;

	const char* get_name() const;
	const char* get_eng() const;
	int get_age() const;
};