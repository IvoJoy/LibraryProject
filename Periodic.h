#pragma once
#include "MyString.h"
#include "Edition.h"
#include "Period.h"

class Periodic : public Edition {
	periodType period;
	size_t number;

public:
	Periodic();
	Periodic(MyString title, MyString description, size_t publishYear, periodType period, size_t number);

	Edition* clone() const override;

	void print() const override;

	bool isBiggerPeriodic(const Periodic* other) const override;
	bool isBigger(const Edition* other) const override;

	std::ostream& write(std::ostream& os) const override;
	std::istream& read(std::istream& is) override;
};
