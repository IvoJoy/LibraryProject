#pragma once
#include "Edition.h"
#include "MyString.h"
#include "UniquePointer.hpp"
#include "Vector.hpp"


class User {
	MyString name;
	Vector<size_t> returned;
	Vector<size_t> currentlyTaken;
	Vector<long long> times;

public:
	User();
	User(const MyString& name);

	const MyString& getName() const;

	int operator[](size_t editionId) const;
	User& operator+=(const Edition* edition);
	User& operator-=(const Edition* edition);

	const Vector<long long>& getTimes() const;
	const Vector<size_t>& getTaken() const;

	friend bool operator>(const User& left, const User& right);
	friend bool operator>=(const User& left, const User& right);
	friend bool operator<(const User& left, const User& right);
	friend bool operator<=(const User& left, const User& right);

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);
};

bool operator==(const User& left, const User& right);
bool operator!=(const User& left, const User& right);


