#pragma once
#include "MyString.h"

class Periodic;

class Edition
{
protected:
	MyString title;
	MyString description;
	size_t libID;
	size_t publishYear;
	static size_t libIDCounter;
	size_t totalNumber;
	size_t takenNumber;

public:
	Edition();
	Edition(MyString title, MyString description, size_t publishYear, size_t totalNumber = 0, size_t takenNumber = 0);

	virtual Edition* clone() const = 0;

	static size_t getIdCounter();
	size_t getId() const;
	size_t getPublishYear() const;
	const MyString& getTitle() const;
	size_t getTotalNumber() const;
	size_t getTakenNumber() const;

	static void setIdCounter(size_t idCounter);
	void setTotalNumber(size_t totalNumber);
	void setTakenNumber(size_t takenNumber);

	virtual void print() const;

	virtual std::ostream& write(std::ostream& os) const;
	virtual std::istream& read(std::istream& is);

	virtual bool isBiggerPeriodic(const Periodic* other) const;
	virtual bool isBigger(const Edition* edition) const;

	virtual ~Edition() = default;
};

bool operator==(const Edition& left, const Edition& right);
