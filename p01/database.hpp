#pragma once

#include "varlenString.hpp"
#include "plane.hpp"
#include <fstream>

class Database {
	std::fstream file;
public:
	Database(const char *fname);
	~Database();

	Plane getPlane(int id);
	void savePlane(const Plane &plane);
};
