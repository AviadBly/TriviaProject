#pragma once
#include <string>
#include <iostream>

class User
{
public:

	User(const std::string& name, const std::string& password, const std::string& mail);
	User() = default;
	

	const std::string& getName() const;
	void setName(const std::string& name);

	const std::string& getPassword() const;
	void setPassword(const std::string& password);

	const std::string& getMail() const;
	void setMail(const std::string& mail);



private:
	std::string m_password;
	std::string m_name;
	std::string m_mail;
};