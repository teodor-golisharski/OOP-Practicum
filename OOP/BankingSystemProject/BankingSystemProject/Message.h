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

	const char* get_message() const;

	Message(const Message& other);
	Message(Message&& other) noexcept;

	Message& operator=(const Message& other);
	Message& operator=(Message&& other) noexcept;

	~Message();
};