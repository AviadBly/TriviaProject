#pragma once
#include <string>

class LoggedUser {

public:
	std::string getUsername() const;

private:
	std::string m_username;
};