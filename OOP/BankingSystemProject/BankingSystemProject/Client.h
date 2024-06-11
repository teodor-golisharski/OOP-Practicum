#pragma once
#include "User.h"
#include "Message.h"
#include "Account.h"

class Client : public User {
private:
	Message* messages;
	Account* accounts;

	void free();
	void moveFrom();
	void copyFrom();

public:
	Client();
	Client(const char* name, const char* egn, unsigned age);
	Client(const Client& other);
	Client(Client&& other);

	~Client();

	double check_avl(const char* bank_name, unsigned account_number);
	void open(const char* bank_name);
	void close(const char* bank_name, unsigned account_number);
	void redeem(const char* bank_name, unsigned account_number, const char* verification_code);
	void change(const char* new_bank_name, const char* current_bank_name, unsigned account_number);
	void list(const char* bank_name) const;
	void messages() const;
};