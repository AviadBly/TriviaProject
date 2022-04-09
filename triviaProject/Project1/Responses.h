#pragma once
#include <string>

class Response {
	unsigned int status;
};

class LoginResponse : public Response {
	std::string username;
	std::string password;
};

class SignUpResponse : public LoginResponse {
	std::string email;
};