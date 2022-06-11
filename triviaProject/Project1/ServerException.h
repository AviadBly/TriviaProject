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

	unsigned char getStatus() const { return this->m_status; }

protected:
	unsigned char m_status;
	std::string m_message;
};
