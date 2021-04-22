#pragma once
#include <cstddef> // nullptr, size_t
#include <istream>
#include <ostream>

class String {
	size_t capacity = 0;
	size_t used = 0;
	char *data = nullptr;

	void ensureCapacity(int target);

public:
	String();
	String(const char *str);
	String(const char *str, int len);
	// String(const char c, int N); // Copy c N times.
	// inhibit(char *buf, int len); // Take possession of the given memory.

	// getters
	size_t size() const;
	const char* getData() const;

	// io
	friend std::istream& operator>>(std::istream &is, String &s);
	friend std::ostream& operator<<(std::ostream &os, const String &s);

	// operators
	String& operator+=(const char *str);
	String& operator+=(const char c);
	String& operator+=(const String &rhs);
	bool operator==(const String &rhs) const;

	// Construct a new String from parts of the data in the current.
	String slice(size_t idx, size_t len) const;
};


template<typename T>
String anySerialize(T v) {
	String ser;
	for(int i = 0;i < sizeof(T);i ++) {
		// take a byte v and put it into the char arr
		ser += (char)(v & 0xff);
		v >>= 8;
	}

	return ser;
}

template<typename T>
T anyDeserialize(const String &s) {
	if(s.size() != sizeof(T)) {
		throw std::length_error("Incoming String size does not match type size");
	}

	T v = 0;
	const char *p = s.getData();

	for(int i = sizeof(T)-1;i >= 0;i --) {
		// take a byte from the incoming data s and put it into v
		v <<= 8;
		v |= (unsigned char)p[i];
	}

	return v;
}
