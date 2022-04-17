#pragma once
#include <string>

struct Response {
	unsigned int status;
	const unsigned int status_ok = 2;
	const unsigned int status_error = 5;
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse {
	std::string message;
};
