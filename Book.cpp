#include "Book.h"


Book::Book() : Edition(), author("Null"), publisher("Null") {}

Book::Book(MyString title, MyString description, size_t publishYear, MyString author, MyString publisher, characteristic characteristic, type type,
	targetAudience targetAudience) :
	Edition(title, description, publishYear), author(author), publisher(publisher) {
	getGenre().setCharacteristic(characteristic);
	getGenre().setType(type);
	getGenre().setTargetAudience(targetAudience);
}


Genre& Book::getGenre() {
	return genre;
}

Edition* Book::clone() const {
	return new Book(*this);
}

std::ostream& Book::write(std::ostream& os) const {
	os << "book ";
	return Edition::write(os) << author << ',' << publisher << ',' << genre << '\n';
}

std::istream& Book::read(std::istream& is) {
	Edition::read(is);
	getline(is, author, ',');
	getline(is, publisher, ',');
	MyString buffer;
	getline(is, buffer, '\n');
	genre = buffer.toNumber();

	return is;
}

void Book::print() const {
	std::cout << "book ";
	Edition::print();
}
