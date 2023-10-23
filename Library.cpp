#include "Library.h"
#include <chrono>
#include "Book.h"
#include "Periodic.h"
#include "Comics.h"
#include "fstream"
#include "UniquePointer.hpp"

const int monthInSeconds = 60;

void Library::addEdition(const Edition* edition) {
		for (size_t i = 0; i < editions.len(); i++) {
			if(*editions[i] == *edition) {
				editions[i]->setTotalNumber(editions[i]->getTotalNumber() + 1);
				return;
			}
		}
		editions.pushBack(UniquePointer<Edition>(edition->clone()));
		editions[editions.len() - 1]->setTotalNumber(1);
}

void Library::removeEdition(size_t libId) {
	for (size_t i = 0; i < editions.len(); i++) {
		if (editions[i]->getId() == libId) {
			if (editions[i]->getTakenNumber() != 0)
				throw std::logic_error("All copies must be returned before removing the edition");
			editions.removeAt(i);
		}
	}
}

void Library::addUser(const MyString& name) {
	for(size_t i = 0; i < users.len(); i++) {
		if (users[i] == name)
			throw std::logic_error("user with this name already exists");
	}
	users.pushBack(name);
}

void Library::removeUser(const MyString& name) {
	for (size_t i = 0; i < users.len(); i++) {
		if (users[i] == name) {
			users.removeAt(i);
			return;
		}
	}
}

void Library::takeEdition(const MyString& name, size_t libId) {
	User* user = nullptr;
	for (size_t i = 0; i < users.len(); i++) {
		if (users[i] == name) {
			user = &users[i];
		}
	}

	for (size_t i = 0; i < editions.len(); i++) {
		if (editions[i]->getId() == libId) {
			*user += &*editions[i];
			editions[i]->setTakenNumber(editions[i]->getTakenNumber() + 1);
		}
	}
}

void Library::returnEdition(const MyString& name, size_t libId) {
	User* user = nullptr;
	for (size_t i = 0; i < users.len(); i++) {
		if (users[i] == name) {
			user = &users[i];
		}
	}

	for (size_t i = 0; i < editions.len(); i++) {
		if (editions[i]->getId() == libId) {
			*user -= &*editions[i];
			editions[i]->setTakenNumber(editions[i]->getTakenNumber() - 1);
		}
	}
}

void Library::readUsers() {
	std::ifstream file("users.csv");

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	while(!file.eof()) {
		User user;
		file >> user;
		if (file.eof())
			return;
		users.pushBack(std::move(user));
	}

	file.close();
}

void Library::readEditions() {
	std::ifstream file("editions.csv");
	
	if (!file.is_open())
		throw std::runtime_error("couldnt open file");
	
	while (!file.eof()) {
		MyString type;
		getline(file, type, ' ');

		if (file.eof())
			return;

		Edition* edition;
		if (type == "book")
			edition = new Book();
		else if (type == "comics")
			edition = new Comics();
		else if (type == "periodic")
			edition = new Periodic();
		else
			throw std::invalid_argument("invalid type");
		
		edition->read(file);
		editions.pushBack(UniquePointer<Edition>(edition));
	}
	
	file.close();
}

void Library::writeEditions() const {
	std::ofstream file("editions.csv");

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	for (size_t i = 0; i < editions.len(); i++)
		editions[i]->write(file);

	file.close();
}


void Library::read() {
	readUsers();
	readEditions();

	std::ifstream file("idCounter.txt");

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	size_t idCounter;

	file >> idCounter;

	Edition::setIdCounter(idCounter);

	file.close();
}

void Library::writeUsers() const {
	std::ofstream file("users.csv");

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	for (size_t i = 0; i < users.len(); i++)
		file << users[i];

	file.close();
}


void Library::write() const {
	writeUsers();
	writeEditions();

	std::ofstream file("idCounter.txt");

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	file << Edition::getIdCounter();

	file.close();
}

void Library::sort(Vector<UniquePointer<Edition>>& _editions) {
	bool isSorted = false;
	size_t j = 0;
	while (!isSorted) {
		isSorted = true;
		for (int i = 0; i < (int)_editions.len() - 1 - (int)j; i++) {
			if (_editions[i]->isBigger(&*_editions[i + 1])) {
				UniquePointer<Edition> temp(std::move(_editions[i]));
				_editions[i] = std::move(_editions[i + 1]);
				_editions[i + 1] = std::move(temp);
				isSorted = false;
			}
		}
		j++;
	}
}


void Library::printSorted() {
	sort(editions);

	for (size_t i = 0; i < editions.len(); i++) {
		editions[i]->print();
		std::cout << '\n';
	}
}

void Library::printExpired() {
	Vector<UniquePointer<Edition>> expired;

	for(size_t i = 0; i < users.len(); i++) {
		Vector<long long> times = users[i].getTimes();

		for(size_t j = 0; j < times.len(); j++) {
			auto duration = std::chrono::system_clock::now().time_since_epoch();
			long long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

			if((seconds - times[j]) > monthInSeconds) {
				for(size_t k = 0; k < editions.len(); k++) {
					if(editions[k]->getId() == users[i].getTaken()[j]) {
						expired.pushBack(UniquePointer<Edition>(editions[k]->clone()));
						break;
					}
				}
			}
		}
	}
	sort(expired);
	for (size_t i = 0; i < expired.len(); i++) {
		expired[i]->print();
		std::cout << '\n';
	}
}


