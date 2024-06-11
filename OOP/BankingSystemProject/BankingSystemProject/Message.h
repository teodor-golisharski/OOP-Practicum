#pragma once

class Message final {
private:
	char* message;

	void copyFrom();
	void moveFrom();
	void free();

public:
	Message();
	Message(const char* message);

	Message(const Message& other);
	Message(Message&& other);

	void operator=(const Message& other);
	void operator=(Message&& other);

	~Message();
};