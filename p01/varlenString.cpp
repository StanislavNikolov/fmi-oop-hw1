#include <cassert>
#include <cstring>
#include <cstdio>

#include "varlenString.hpp"

String::String() { }

String::String(const char *str) {
	const size_t len = strlen(str);
	ensureCapacity(len);
	memcpy(data, str, len);
	used = len;
}

String::String(const char *str, int len) {
	ensureCapacity(len);
	memcpy(data, str, len);
	used = len;
}

size_t String::size() const { return used; }
const char* String::getData() const { return data; }

void String::ensureCapacity(int target) {
	if(capacity >= target) return;

	// TODO do doubling of capacity by finding the smallest power of 2 greater
	// than target

	// there is nothing that can be done on std::bad_alloc, just pass on
	// the exception
	char *newData = new char[target];
	capacity = target;

	// move the old data to the new location, free the old data
	std::memcpy(newData, data, used);
	delete[] data;
	data = newData;
}

std::istream& operator>>(std::istream &is, String &s) {
	is >> std::ws; // remove leading whitespace

	while(true) {
		// better than using .get() and .unget()
		int nextChar = is.peek();
		if(nextChar == EOF || isspace(nextChar)) break;
		s += is.get();
	}

	return is;
}

std::ostream& operator<<(std::ostream &os, const String &s) {
	// TODO do it in bulk instead of the inefficent single char by char
	for(int i = 0;i < s.used;i ++) {
		os << s.data[i];
	}

	return os;
}

String& String::operator+=(const char *str) {
	const size_t nsLen = std::strlen(str);

	// make sure we have enough capacity to handle the new data
	ensureCapacity(nsLen + used);

	// append the new string to the existing buff
	std::memcpy(data + used, str, nsLen);
	used += nsLen;

	return *this;
}

String& String::operator+=(const char c) {
	ensureCapacity(used + 1);
	data[used ++] = c;
	return *this;
}

bool String::operator==(const String &rhs) const {
	if(used != rhs.used) return false;

	for(size_t i = 0;i < used;i ++) {
		if(data[i] != rhs.data[i]) return false;
	}

	return true;
}

String& String::operator+=(const String &rhs) {
	// make sure we have enough capacity to handle the new data
	ensureCapacity(used + rhs.used);

	// append the new data to the existing buff
	std::memcpy(data + used, rhs.data, rhs.used);
	used += rhs.used;

	return *this;
}

String String::slice(size_t idx, size_t len) const {
	if(idx + len > used) {
		throw std::out_of_range("Slice arguments request out of range access");
	}

	return String(data + idx, len);
}
