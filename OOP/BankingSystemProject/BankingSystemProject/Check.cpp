#include "Check.h"
#include <ctime>

Check::Check() = default;

Check::Check(double sum) {

	transaction_sum = sum;

	unsigned int seed = static_cast<unsigned int>(std::time(0));
	for (short i = 0; i < 3; i++) {
		id[i] = generate_random_char(seed);
	}
	
}

Check::~Check() = default;

const char* Check::get_id() const {
	return this->id;
}

double Check::get_transaction_sum() const {
	return this->transaction_sum;
}

char generate_random_char(unsigned int& seed) {
	const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	const size_t max_index = sizeof(charset) - 1;
	
	seed = seed * 1103515245 + 12345;
	return charset[(seed / 65536) % max_index];
}
