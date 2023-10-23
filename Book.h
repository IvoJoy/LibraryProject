#pragma once
#include "MyString.h"
#include "Edition.h"
#include "Genre.h"

class Book : public Edition {
	MyString author;
	MyString publisher;
	Genre genre;

public:
	Book();
	Book(MyString title, MyString description, size_t publishYear, MyString author, MyString publisher, characteristic characteristic, type type, 
		targetAudience targetAudience);

	Edition* clone() const override;

	Genre& getGenre();
	//we return non-constant reference, so that we can use the reference to the Genre so we can set things in it (ex: setType)

	void print() const override;

	std::ostream& write(std::ostream& os) const override;
	std::istream& read(std::istream& is) override;
};
