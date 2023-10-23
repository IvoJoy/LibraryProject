#include "Genre.h"
#include <iostream>


void Genre::setCharacteristic(characteristic characteristic) {
	genre &= 0xFF80;
	genre |= characteristic;
	setControlBit();
}

void Genre::setType(type type) {
	genre &= 0xF87F;
	genre |= (type << 7);
	setControlBit();
}

void Genre::setTargetAudience(targetAudience targetAudience) {
	genre &= 0x87FF;
	genre |= (targetAudience << 11);
	setControlBit();
}

characteristic Genre::getCharacteristic() const {
	return characteristic(genre & 0x7F);
}

type Genre::getType() const {
	return type((genre & 0x780) >> 7);
}

targetAudience Genre::getTargetAudience() const {
	return targetAudience((genre & 0x7800) >> 11);
}

void Genre::setControlBit() {
	size_t onesCount = 0;

	for(size_t i = 1; i < 0x8000; i <<= 1) {
		if ((genre & i) != 0)
			onesCount++;
	}
	size_t mask = onesCount % 2 == 0 ? 0 : 1;
	mask <<= 15;
	genre |= mask;
}

std::ostream& operator<<(std::ostream& os, const Genre& genre) {
	return os << genre.genre;
}

std::istream& operator>>(std::istream& is, Genre& genre) {
	return is >> genre.genre;
}

Genre& Genre::operator=(unsigned short genre) {
	this->genre = genre;
	return *this;
}

