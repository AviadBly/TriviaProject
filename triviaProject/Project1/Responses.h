#pragma once
#include <string>

#define SIGN_RESPONSE_CODE 10
#define LOGIN_RESPONSE_CODE 20
#define ERROR_RESPONSE_CODE 50

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