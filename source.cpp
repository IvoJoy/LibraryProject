#include <chrono>
#include <iostream>
#include "Library.h"
#include "Book.h"
#include "Comics.h"
#include "Periodic.h"
#include <thread>

int main() {
	//Library lib;
	//lib.addUser("pesho");
	//lib.addUser("gosho");

	//Book book("the witcher last wish", "very good", 2000, 
	//	"Andrej Sapkowski", "something",  characteristic::action, type::prose, targetAudience::teens);
	//book.getGenre().setCharacteristic(characteristic::action);

	//Book book2("the witcher season of storms", "very good", 2000, 
	//	"Andrej Sapkowski", "something",  characteristic::action, type::prose, targetAudience::teens);
	//Comics comics("Monster", "goated", 200, "something", "something", 
	//	periodType::Weekly, 2,
	//	characteristic::action, type::prose, targetAudience::teens);

	//Periodic periodic1("solo leveling", "something", 2000, periodType::Monthly, 1);
	//Periodic periodic2("something", "something", 2000, periodType::Monthly, 1);
	//Periodic periodic3("something", "something", 2000, periodType::Monthly, 2);

	//lib.addEdition(&periodic1);
	//lib.addEdition(&book);
	//lib.addEdition(&book2);
	//lib.addEdition(&periodic3);
	//lib.addEdition(&book2);
	//lib.addEdition(&comics);
	//lib.addEdition(&periodic2);

	//lib.takeEdition("gosho", 1);
	//lib.takeEdition("gosho", 2);
	//lib.returnEdition("gosho", 2);
	//lib.write();

	Library lib;
	lib.read();
	lib.write();
	lib.printExpired();

	//auto duration = std::chrono::system_clock::now().time_since_epoch();
	//auto s = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

	//std::this_thread::sleep_for(std::chrono::seconds(2));

	//auto duration2 = std::chrono::system_clock::now().time_since_epoch();
	//auto s2 = std::chrono::duration_cast<std::chrono::seconds>(duration2).count();
	//std::cout << s2 - s;
}
