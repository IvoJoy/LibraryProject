#include "User.h"

#include <chrono>
#include <sstream>

User::User() : name("Null") {}

User::User(const MyString& name) : name(name) {}

const MyString& User::getName() const {
	return name;
}

bool operator==(const User& left, const User& right) {
	return left.getName() == right.getName();
}

bool operator!=(const User& left, const User& right) {
	return !(left == right);
}

int User::operator[](size_t editionId) const {
	for(size_t i = 0; i < currentlyTaken.len(); i++) {
		if (editionId == currentlyTaken[i])
			return 1;
	}
	for (size_t i = 0; i < returned.len(); i++) {
		if (editionId == returned[i])
			return 0;
	}
	return -1;
}

bool operator<(const User& left, const User& right) {
	return left.returned.len() < right.returned.len();
}

bool operator<=(const User& left, const User& right) {
	return left.returned.len() <= right.returned.len();
}

bool operator>(const User& left, const User& right) {
	return !(left <= right);
}

bool operator>=(const User& left, const User& right) {
	return !(left < right);
}

User& User::operator+=(const Edition* edition) {
	if ((*this)[edition->getId()] == 1)
		throw std::logic_error("already taken");

	if (currentlyTaken.len() >= 5)
		throw std::logic_error("user has taken 5 editions already");

	currentlyTaken.pushBack(edition->getId());
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	long long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	times.pushBack(seconds);

	return *this;
}

User& User::operator-=(const Edition* edition) {
	if ((*this)[edition->getId()] != 1)
		throw std::logic_error("not taken");
	if ((*this)[edition->getId()] != 0)
		returned.pushBack(edition->getId());

	for (size_t i = 0; i < currentlyTaken.len(); i++) {
		if (edition->getId() == currentlyTaken[i]) {
			currentlyTaken.removeAt(i);
			times.removeAt(i);
			break;
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
	os << user.name << ',';
	for (size_t i = 0; i < user.returned.len(); i++)
		os << user.returned[i] << ' ';
	os << ',';
	for (size_t i = 0; i < user.currentlyTaken.len(); i++)
		os << user.currentlyTaken[i] << ' ';
	os << ',';
	for (size_t i = 0; i < user.times.len(); i++)
		os << user.times[i] << ' ';
	os << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, User& user) {
	getline(is, user.name, ',');

	MyString buffer;

	getline(is, buffer, ',');

	std::stringstream ss(buffer.c_str());

	while(!ss.eof()) {
		size_t id;
		if(ss >> id)
			user.returned.pushBack(id);
	}

	getline(is, buffer, ',');

	std::stringstream ss2(buffer.c_str());

	while (!ss2.eof()) {
		size_t id;
		if(ss2 >> id)
			user.currentlyTaken.pushBack(id);
	}

	getline(is, buffer, '\n');

	std::stringstream ss3(buffer.c_str());

	while (!ss3.eof()) {
		long long time;
		if (ss3 >> time)
			user.times.pushBack(time);
	}
	return is;
}

const Vector<size_t>& User::getTaken() const {
	return currentlyTaken;
}

const Vector<long long>& User::getTimes() const {
	return times;
}


