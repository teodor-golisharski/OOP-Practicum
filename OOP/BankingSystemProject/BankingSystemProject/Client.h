#pragma once
#include "User.h"
#include "Account.h"
#include "BasicVector.hpp"
#include "Check.h"

class Client : public User {
private:
	BasicVector<MyString> messages;
	BasicVector<Account> accounts;
	BasicVector<Check> checks;

	void add_account(const Account& account);
	void remove_account(const char* accountNumber);
public:
	Client();
	Client(const MyString& name, const char egn[EGN_LENGTH], unsigned age, const MyString& password);

	virtual ~Client();

	void redeem_check(const char* verification_code, Account& account);
	void help() const override;
	
	unsigned find_account_index(const char* account_number) const;
	Account& find_account(const char* account_number) const;
	BasicVector<Account> get_accounts(const MyString& bank_name) const;
	unsigned get_messages_count() const;
	MyString get_message_at_index(unsigned index) const;
	bool has_accounts_in_bank(const MyString& bank_name);
	void receive_check(const Check& check);
	void receive_message(const MyString& message);
};