#pragma once
#include "User.h"
#include "Message.h"
#include "Account.h"
#include "BasicVector.hpp"


class Bank;

class Client : public User {
private:
	BasicVector<Message> messages;
	BasicVector<Account> accounts;

	unsigned find_account(const char* account_number) const;

	//void add_account(const Account& account);
	//void close_account(const char* accountNumber);

	friend class Bank;
public:
	Client();
	Client(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password);

	virtual ~Client();

	double check_avl(const MyString& bank_name, const char* account_number) const;
	void help() const override;
	
	//void redeem(const char* bank_name, unsigned account_number, const char* verification_code);
	
	
	//void change(const char* new_bank_name, const char* current_bank_name, unsigned account_number);
	//void list(const char* bank_name) const;
	//void show_messages() const;
};