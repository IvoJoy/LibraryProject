#include "Comics.h"


Comics::Comics() : Edition(), author("Null"), publisher ("Null"), period(periodType::Weekly){}

Comics::Comics(MyString title, MyString description, size_t publishYear, MyString author, MyString publisher,
										 periodType period, size_t number, characteristic characteristic, type type,
	targetAudience targetAudience) :
	Edition(title, description, publishYear), author(author), publisher (publisher), period(period), number(number) {
	getGenre().setCharacteristic(characteristic);
	getGenre().setType(type);
	getGenre().setTargetAudience(targetAudience);
}

Genre& Comics::getGenre() {
	return genre;
}


Edition* Comics::clone() const {
	return new Comics(*this);
}

std::ostream& Comics::write(std::ostream& os) const {
	os << "comics ";
	return Edition::write(os) << author << ',' << publisher << ',' << genre << ',' << period << ',' << number << '\n';
}

std::istream& Comics::read(std::istream& is) {
	Edition::read(is);
	getline(is, author, ',');
	getline(is, publisher, ',');
	MyString buffer;
	getline(is, buffer, ',');
	genre = buffer.toNumber();
	getline(is, buffer, ',');
	period = (periodType)buffer.toNumber();
	getline(is, buffer, '\n');
	number = buffer.toNumber();

	return is;
}

void Comics::print() const {
	std::cout << "Comics ";
	Edition::print();
}
