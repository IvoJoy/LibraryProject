#pragma once
#include "User.h"
#include "Vector.hpp"
#include "Edition.h"

class Library {
	Vector<User> users;
	Vector<UniquePointer<Edition>> editions;

	void writeEditions() const;
	void writeUsers() const;

	void readEditions();
	void readUsers();

	void sort(Vector<UniquePointer<Edition>>& editions);

public:
	void addEdition(const Edition* edition);

	void removeEdition(size_t libId) ;

	void addUser(const MyString& name);
	void removeUser(const MyString& name);

	void takeEdition(const MyString& name, size_t libId);
	void returnEdition(const MyString& name, size_t libId);

	void printSorted();
	void printExpired();

	void read();
	void write() const;
};
