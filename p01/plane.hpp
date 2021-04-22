#pragma once

#include "varlenString.hpp"
#include <istream>

class Plane {
	int id;
	String name;
	char type[21];
	int flights;

public:
	Plane();
	Plane(int id, const char *name, const char *type, int flights);
	Plane(const String &s);

	friend std::istream& operator>>(std::istream& is, Plane &plane);
	friend std::ostream& operator<<(std::ostream& is, const Plane &plane);

	int getId() const;
	String serialize() const;
};
