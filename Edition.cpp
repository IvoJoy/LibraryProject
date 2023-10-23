#include "Edition.h"


size_t Edition::libIDCounter = 1;

Edition::Edition() : title("Null"), description("Null"), libID(0), publishYear(0){}

Edition::Edition(MyString title, MyString description, size_t publishYear, size_t totalNumber, size_t takenNumber) :
title(title), description(description), libID(libIDCounter++), publishYear(publishYear), totalNumber(totalNumber), takenNumber(takenNumber){}

size_t Edition::getIdCounter() {
	return libIDCounter;
}

size_t Edition::getId() const {
	return libID;
}

bool operator==(const Edition& left, const Edition& right) {
	return left.getId() == right.getId();
}

size_t Edition::getTakenNumber() const {
	return takenNumber;
}

size_t Edition::getTotalNumber() const {
	return totalNumber;
}

void Edition::setIdCounter(size_t idCounter) {
	libIDCounter = idCounter;
}

void Edition::setTakenNumber(size_t _takenNumber) {
	takenNumber = _takenNumber;
}

void Edition::setTotalNumber(size_t _totalNumber) {
	totalNumber = _totalNumber;
}

std::ostream& Edition::write(std::ostream& os) const {
	return os << title << ',' << description << ',' << libID << ','
				<< publishYear << ',' << totalNumber << ',' << takenNumber << ',';
}

std::istream& Edition::read(std::istream& is) {
	getline(is, title, ',');
		getline(is, description, ',');
		MyString buffer;
		getline(is, buffer, ',');
		libID = buffer.toNumber();
		getline(is, buffer, ',');
		publishYear = buffer.toNumber();
		getline(is, buffer, ',');
		totalNumber = buffer.toNumber();
		getline(is, buffer, ',');
		takenNumber = buffer.toNumber();
	
		return is;
}

bool Edition::isBiggerPeriodic(const Periodic* other) const {
	return isBigger((Edition*)other);
}

bool Edition::isBigger(const Edition* other) const {
	if (publishYear == other->publishYear)
		return std::strcmp(title.c_str(), other->title.c_str()) > 0;
	return publishYear > other->publishYear;
}

void Edition::print() const {
	std::cout << title << ' ' << description << ' ' << libID;
}

const MyString& Edition::getTitle() const {
	return title;
}

size_t Edition::getPublishYear() const {
	return publishYear;
}







