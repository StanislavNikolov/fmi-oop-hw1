#include "bcrypt/BCrypt.hpp"
#include <iostream>

int main(){
	std::string password = "test";
	std::string hash = BCrypt::generateHash(password);

	std::cout << BCrypt::validatePassword(password,hash) << std::endl;
	std::cout << BCrypt::validatePassword("test1",hash) << std::endl;

	return 0;
}
