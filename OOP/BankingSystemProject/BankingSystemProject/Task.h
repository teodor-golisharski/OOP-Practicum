#pragma once

class Task final {
private:
	char* name;
	enum type { Open, Close, Change };
	unsigned int id;

	void copyFrom(const Task& other);
	void moveFrom(Task&& other);
	void free();
public:
	Task();
	Task(char* name, type e, unsigned int id);

	Task(const Task& other);
	Task(Task&& other) noexcept;

	Task& operator=(const Task& other);
	Task& operator=(Task&& other) noexcept;

	~Task();

	const char* get_task_name() const;
	const char* get_task_type() const;
	const unsigned int get_task_id() const;
};