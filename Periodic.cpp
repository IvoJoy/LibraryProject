#include "Periodic.h"

Periodic::Periodic() : Edition(), period(periodType::Weekly), number (0) {}

Periodic::Periodic(MyString title, MyString description, size_t publishYear, periodType period, size_t number) : 
	Edition(title, description, publishYear), period(period), number(number) {}


Edition* Periodic::clone() const {
	return new Periodic(*this);
}

std::ostream& Periodic::write(std::ostream& os) const {
	os << "periodic ";
	return Edition::write(os) << period << ',' << number << '\n';
}

std::istream& Periodic::read(std::istream& is) {
	Edition::read(is);
	MyString buffer;
	getline(is, buffer, ',');
	period = (periodType)buffer.toNumber();
	getline(is, buffer, '\n');
	number = buffer.toNumber();

	return is;
}

void Periodic::print() const {
	std::cout << "periodic ";
	Edition::print();
}

bool Periodic::isBigger(const Edition* other) const {
	return !other->isBiggerPeriodic(this);
}

bool Periodic::isBiggerPeriodic(const Periodic* other) const {
	if (publishYear == other->getPublishYear()) {
		if (std::strcmp(title.c_str(), other->getTitle().c_str()) == 0)
			return number > other->number;
		return std::strcmp(title.c_str(), other->getTitle().c_str()) > 0;
	}
	return publishYear > other->getPublishYear();
}
