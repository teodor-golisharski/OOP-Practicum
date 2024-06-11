#include "Message.h"
#include<iostream>

void Message::copyFrom(const Message& other) {
	size_t size = strlen(other.message)+1;
	this->message = new char[size];
	strcpy_s(message,size, other.message);
}

void Message::moveFrom(Message&& other) {
	message = other.message;
	other.message = nullptr;
}

void Message::free() {
	delete[] message;
}

Message::Message() : Message("") {}

Message::Message(const char* message) {
	size_t size = strlen(message) + 1;
	this->message = new char[size];
	strcpy_s(this->message, size, message);
}

Message::Message(const Message& other) {
	copyFrom(other);
}

Message::Message(Message&& other) {
	moveFrom(std::move(other));
}

Message& Message::operator=(const Message& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Message& Message::operator=(Message&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Message::~Message() {
	free();
}

