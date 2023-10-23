#pragma once
#include <iostream>

enum characteristic {
	fantasy,
	thriller,
	action,
	scifi,
	history,
	biography,
	comedy,
	romance
};

enum type {
	drama,
	prose,
	poetry,
	schoolbook,
	novel,
	novella,
	shortstory
};

enum targetAudience {
	kids,
	teens,
	adults,
	seniors
};

class Genre {
	unsigned short genre = 0;

	void setControlBit();
	
public:
	void setCharacteristic(characteristic characteristic);
	void setType(type type);
	void setTargetAudience(targetAudience targetAudience);

	characteristic getCharacteristic() const;
	type getType() const;
	targetAudience getTargetAudience() const;

	Genre& operator=(unsigned short genre);

	friend std::ostream& operator<<(std::ostream& os, const Genre& genre);
	friend std::istream& operator>>(std::istream& os, Genre& genre);
};