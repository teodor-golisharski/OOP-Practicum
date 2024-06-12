#pragma once
#include "User.h"
#include "Message.h"
#include "Account.h"
#include "Controller.h"

class Client : public User {
private:
	Message* messages;
	Account* accounts;

	void free();
	void moveFrom(Client&& other);
	void copyFrom(const Client& other);

	Account& find_account(const char* account_number);
public:
	Client();
	Client(const char* name, const char* egn, unsigned age, const char* password);
	Client(const Client& other);
	Client(Client&& other);

	virtual ~Client();

	double check_avl(const char* bank_name, unsigned account_number);
	void open(const char* bank_name);
	void close(const char* bank_name, unsigned account_number);
	void redeem(const char* bank_name, unsigned account_number, const char* verification_code);
	void change(const char* new_bank_name, const char* current_bank_name, unsigned account_number);
	void list(const char* bank_name) const;
	void show_messages() const;
};