#include "plane.hpp"
#include "varlenString.hpp"

Plane::Plane() { }
Plane::Plane(int id, const char *name, const char *type, int flights) {
	const size_t typeLen = strlen(type);
	if(typeLen > 20) {
		throw std::invalid_argument("Type is too long");
	}
	this->id = id;
	this->name = String(name);
	strncpy(this->type, type, typeLen+1);
	this->flights = flights;
}
int Plane::getId() const { return id; }

std::istream& operator>>(std::istream& is, Plane &plane) {
	is >> plane.id >> plane.name >> plane.type >> plane.flights;
	return is;
}

std::ostream& operator<<(std::ostream &os, const Plane &plane) {
	os << plane.id << ' ' << plane.name << ' ' << plane.type << ' ' << plane.flights;
	return os;
}

Plane::Plane(const String &s) {
	// IMPORTANT - keep code in sync with Plane::serialize()
	id = anyDeserialize<int>(s.slice(0, 4));
	strcpy(type, s.slice(4, 20).getData());
	type[20] = '\0';

	flights = anyDeserialize<int>(s.slice(24, 4));
	name = s.slice(28, s.size()-28);
}

String Plane::serialize() const {
	// IMPORTANT - keep code in sync with Plane::Plane(const String &s)

	String ser;

	ser += anySerialize<int>(id);
	ser += type;
	// Pad empty bytes with zeros, but do not put null terminator if type is full
	for(int i = strlen(type);i < sizeof(type)-1;i ++) {
		ser += (char)0;
	}

	ser += anySerialize<int>(flights);
	ser += name;

	return ser;
}
