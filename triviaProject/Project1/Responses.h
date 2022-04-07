#pragma once
#include <string>

struct Response {
	unsigned int status;
};

struct ErrorResponse : public Response {
	std::string message;
};

struct LoginResponse : public Response {
	std::string username;
	std::string password;
};

struct SignUpResponse : public LoginResponse {
	std::string email;
};