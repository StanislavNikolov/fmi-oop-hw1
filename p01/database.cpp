#include "database.hpp"
#include "varlenString.hpp"

Database::Database(const char *fname) {
	file.open(fname, std::fstream::in | std::fstream::out | std::ios::binary | std::ios::app);
}

Database::~Database() {
	file.close();
}

void Database::savePlane(const Plane &plane) {
	bool alreadyInDB = true;
	try {
		getPlane(plane.getId());
	} catch(const std::exception &e) {
		// Actually we want this exception to happen - no such id exists and we
		// can continue.
		alreadyInDB = false;
	}

	if(alreadyInDB) {
		throw std::runtime_error("Plane already exists");
	}

	String payload = plane.serialize(); // plane data
	String header = anySerialize(payload.size()); // header - length of plane data

	file.clear();
	//file.seekp(0, std::ios_base::end); // append to file
	file.write(header.getData(), header.size());
	file.write(payload.getData(), payload.size());
	file.flush();
}

Plane Database::getPlane(int id) {
	// inefficent - O(N)
	// Can be improved with persistent in-memory storage of the planes and
	// adding a hashmap for example. Also, loading the whole db into memory for
	// every query is dumb, but deadlines be deadlines

	// start at the begining of the file
	file.clear();
	file.seekg(0);

	// check if file is empty
	if(file.peek() == EOF) {
		throw std::invalid_argument("No such plane id in the DB");
	}

	// TODO safery checks - for example if all reads are successful
	while(!file.eof()) {
		// read header containing payload length
		char headerBuf[8];
		file.read(headerBuf, 8);
		size_t payloadLen = anyDeserialize<size_t>(String(headerBuf, 8));

		// read the payload
		char *rawPayload = new char[payloadLen];
		file.read(rawPayload, payloadLen);
		String payload(rawPayload, payloadLen);
		delete[] rawPayload;

		// parse the payload into a plane
		Plane plane(payload);

		// return if this is the plane we are looking for
		if(plane.getId() == id) return plane;
	}

	throw std::invalid_argument("No such plane id in the DB");
}
