#pragma once

#include "GlobalConstants.h"
#include "BasicVector.hpp"

class Check final {
private:
	char code[CODE_LENGTH];
	double transaction_sum;

	static BasicVector<char*> codes_in_use;

	bool is_correct_format(char* code);
	bool is_alpha_numeric(char* code);
	bool is_unique(char* code, BasicVector<char*> codes);
public:
	Check();
	Check(char* code, double sum);

	const char* get_check_code() const;
	const double get_tansaction_sum() const;

	~Check();
};