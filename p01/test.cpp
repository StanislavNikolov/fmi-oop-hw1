#include <iostream>
#include "varlenString.hpp"
#include "plane.hpp"

// useful debugging functions
void hex(unsigned char c) {
	char table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	std::cout << table[c>>4] << table[c%16];
}

void hexprint(const String &s) {
	auto p = s.getData();
	std::cout << "hex: ";
	for(int i = 0;i < s.size();i ++) {
		hex(p[i]);
		std::cout << ' ';
	}
	std::cout << std::endl;
}

void test_String() {
	String s;
	assert(s.size() == 0);

	s += "t";    assert(s.size() == 1);
	s += "e";    assert(s.size() == 2);
	s += "s";    assert(s.size() == 3);
	s += "t123"; assert(s.size() == 7);

	const char *data = s.getData();
	const char target[] = "test123";
	for(int i = 0;i < sizeof(target)-1;i ++) {
		assert(data[i] == target[i]);
	}

	assert(s.slice(1, 2) == "es");
	assert(!(s.slice(1, 2) == "XX"));
	assert(String("es") == s.slice(1,2));
	assert(String("es") == String("es"));
	assert(s.slice(1,2) == s.slice(1,2));
	assert(String("es") == String(String("es")));

	String x;
	x += 'a';
	x += "bc";
	x += 'd';
	assert(x == String("abcd"));
	x += String("ef");
	assert(x == String("abcdef"));
	x += '\0';
	assert(x == String("abcdef\x00", 7));

	assert(String("\x00").size() == 0);
	assert(String("\x00", 1).size() == 1);
}

void test_StringSerialize() {
	assert(anySerialize<int>(0x01) == String("\x01\x00\x00\x00", 4));
	assert(anySerialize<int>(0x0f) == String("\x0f\x00\x00\x00", 4));
	assert(anySerialize<int>(0xff) == String("\xff\x00\x00\x00", 4));

	assert(anySerialize<int>(0x01ff) == String("\xff\x01\x00\x00", 4));
	assert(anySerialize<int>(0xffff) == String("\xff\xff\x00\x00", 4));
	assert(anySerialize<int>(0xdead) == String("\xad\xde\x00\x00", 4));
}

void test_StringDeserialize() {
	assert(anyDeserialize<int>(String("\xad\xde\x00\x00", 4)) == 0xdead);

	for(int i = 0;i <= 0xff;i ++) {
		assert(anyDeserialize<int>(anySerialize<int>(i)) == i);
	}
	for(int i = 0x0100;i <= 0xffff;i += 13) {
		assert(anyDeserialize<int>(anySerialize<int>(i)) == i);
	}
	assert(anyDeserialize<int>(anySerialize<int>(0xdead)) == 0xdead);
}

void test_Plane() {
	Plane pl1(0xdead, "name", "01234567890123456789", 12);
	assert(pl1.getId() == 0xdead);
	assert(pl1.serialize() == pl1.serialize()); // test serialize is reproducable

	// test pl2 is identical to pl1
	Plane pl2(pl1.serialize());
	assert(pl2.getId() == pl1.getId());
	assert(pl2.serialize() == pl1.serialize());
}

int main() {
	test_String();
	std::cout << "String test passed" << std::endl;

	test_StringSerialize();
	std::cout << "String serialization test passed" << std::endl;

	test_Plane();
	std::cout << "All tests passed successfully" << std::endl;

	return 0;
}

