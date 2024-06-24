#pragma once

#include "GlobalConstants.h"
#include "BasicVector.hpp"
#include "MyString.hpp"

class Check final {
private:
	char code[CODE_LENGTH];
	double transaction_sum;
	MyString bank_name;
	char egn[EGN_LENGTH + 1];

	static BasicVector<char*> codes_in_use;

	char generate_random_char(unsigned int& seed);

	bool is_correct_format(char* code);
	bool is_alpha_numeric(char* code);
	bool is_unique(char* code);
public:
	Check();
	Check(double sum, const MyString& bank_name, const char* egn);

	bool verify_check_code(char* code);
	const double get_tansaction_sum() const;
	const MyString get_bank_name() const;
	const char* get_egn() const;
	const char* get_code() const;

	~Check();
};