#pragma once
#include "User.h"
#include "BasicVector.hpp"

class UsersContainer {
private:
	BasicVector<User*> users;

public:
	UsersContainer();
	~UsersContainer();

    UsersContainer(const UsersContainer& other);
    UsersContainer& operator=(const UsersContainer& other);

    UsersContainer(UsersContainer&& other) noexcept;
    UsersContainer& operator=(UsersContainer&& other) noexcept;

    void push(User* item);
    User* get(unsigned index) const;
    size_t size() const;
};