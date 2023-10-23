#pragma once
#include "MyString.h"
#include "Edition.h"
#include "Period.h"
#include "Genre.h"

class Comics : public Edition {
	MyString author;
	MyString publisher;
	Genre genre;
	periodType period;
	size_t number;

public:
	Comics();
	Comics(MyString title, MyString description, size_t publishYear, MyString author, MyString publisher
													, periodType period, size_t number, characteristic characteristic, type type,
		targetAudience targetAudience);

	Edition* clone() const override;

	Genre& getGenre();

	void print() const override;

	std::ostream& write(std::ostream& os) const override;
	std::istream& read(std::istream& is) override;
};
