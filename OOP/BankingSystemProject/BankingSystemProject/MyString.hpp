#pragma once
#include <iostream>

class MyString
{
	char* data;
	size_t len;

	void copyFrom(const MyString& data);
	void free();

	explicit MyString(size_t capacity); 
public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	size_t length() const;
	MyString& operator+=(const MyString& other);

	MyString substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream&, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);


void MyString::copyFrom(const MyString& other) {
    len = other.len;
    data = new char[len + 1];
    std::strcpy(data, other.data);
}

void MyString::free() {
    delete[] data;
}

MyString::MyString() : MyString(1) {
    data[0] = '\0';
}

MyString::MyString(size_t capacity) {
    len = capacity - 1;
    data = new char[capacity];
}

MyString::MyString(const char* str) : MyString(std::strlen(str) + 1) {
    std::strcpy(data, str);
}

MyString::MyString(const MyString& other) {
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString::~MyString() {
    free();
}

MyString::MyString(MyString&& other) noexcept {
    data = other.data;
    len = other.len;
    other.data = nullptr;
    other.len = 0;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        free();
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
    }
    return *this;
}

size_t MyString::length() const {
    return len;
}

MyString& MyString::operator+=(const MyString& other) {
    size_t newLength = len + other.len;
    char* newData = new char[newLength + 1];
    std::strcpy(newData, data);
    std::strcat(newData, other.data);
    delete[] data;
    data = newData;
    len = newLength;
    return *this;
}

MyString MyString::substr(size_t begin, size_t howMany) const {
    if (begin + howMany > len)
        throw std::out_of_range("Substr out of range");

    MyString result(howMany + 1);
    for (size_t i = 0; i < howMany; i++)
        result.data[i] = data[begin + i];
    result.data[howMany] = '\0';
    return result;
}

char& MyString::operator[](size_t index) {
    if (index >= len)
        throw std::out_of_range("Index out of range");
    return data[index];
}

char MyString::operator[](size_t index) const {
    if (index >= len)
        throw std::out_of_range("Index out of range");
    return data[index];
}

const char* MyString::c_str() const {
    return data;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result(lhs.len + rhs.len + 1);
    std::strcpy(result.data, lhs.data);
    std::strcat(result.data, rhs.data);
    return result;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;

    delete[] str.data;
    str.len = std::strlen(buffer);
    str.data = new char[str.len + 1];
    std::strcpy(str.data, buffer);
    return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    return os << str.c_str();
}

bool operator<(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}