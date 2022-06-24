#pragma once
#include <exception>
#include <string>

class ServerException : public std::exception
{
public:
	ServerException(const std::string& message, unsigned char status) : m_message(message), m_status(status) {}
	virtual ~ServerException() noexcept = default;
	virtual const char* what() const noexcept { return m_message.c_str(); }


	const static unsigned char ACTIVELY_DISCONECT_USER_CODE = 66;
	const static unsigned char ROOM_WITH_ID_NOT_FOUND_CODE = 65;
	const static unsigned char USERNAME_ALREADY_EXIST_CODE = 64;
	const static unsigned char WRONG_USERNAME_OR_PASSWORD_CODE = 63;
	const static unsigned char USERNAME_NOT_FOUND = 62;
	const static unsigned char INVALID_USERNAME = 61;
	const static unsigned char INVALID_PASSWORD = 60;
	const static unsigned char ROOM_IS_FULL_CODE = 59;

	unsigned char getStatus() const { return this->m_status; }

protected:
	unsigned char m_status;
	std::string m_message;
};
