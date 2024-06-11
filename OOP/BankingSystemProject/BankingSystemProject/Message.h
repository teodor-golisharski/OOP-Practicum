#pragma once

class Message final {
private:
	char* message;

	void copyFrom(const Message& other);
	void moveFrom(Message&& other);
	void free();

public:
	Message();
	Message(const char* message);

	Message(const Message& other);
	Message(Message&& other);

	Message& operator=(const Message& other);
	Message& operator=(Message&& other);

	~Message();
};