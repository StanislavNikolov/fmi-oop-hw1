#include <iostream>
#include "plane.hpp"
#include "database.hpp"

using std::cout;
using std::cin;
using std::endl;

void search(Database &db) {
	int id;
	cin >> id;
	cin.get(); // leftover whitespace

	try {
		Plane plane = db.getPlane(id);
		std::cout << plane << std::endl;
	} catch(std::exception e) {
		std::cout << "Record not found!" << std::endl;
		return;
	}
}

void create(Database &db) {
	Plane newPlane;
	cin >> newPlane;
	cin.get(); // leftover whitespace

	try {
		db.savePlane(newPlane);
	} catch(const std::exception &e) {
		std::cout << "Can't insert plane" << std::endl;
	}
}

int main(int argc, char *argv[]) {
	const char *fname = (argc > 1 ? argv[1] : "Planes.db");
	cout << "Opening " << fname << endl;
	Database db(fname);

	// command dispatcher
	while(true) {
		cout << "> ";

		char command[10];
		cin.getline(command, sizeof(command));

		if(cin.eof()) return 0;
		if(strcmp(command, "exit") == 0) return 0;

		if(strcmp(command, "create") == 0) {
			cout << "create(id, name, type, flights): ";
			create(db);
			continue;
		}

		if(strcmp(command, "search") == 0) {
			cout << "search(id): ";
			search(db);
			continue;
		}

		cout << "Unrecognized command!" << endl;
	}

	return 0;
}

