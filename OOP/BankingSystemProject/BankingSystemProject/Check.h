#pragma once

class Check final {
private:
	char id[3];
	double transaction_sum;
public:
	Check();
	Check(double sum);

	const char* get_id() const;
	double get_transaction_sum() const;
	~Check();
};