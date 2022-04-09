#include "User.h"
#include <iomanip>


User::User(const std::string& name, const std::string& password, const std::string& mail ) :
	m_mail(mail), m_name(name),m_password(password)
{
	// Left empty
}


const std::string& User::getName() const
{
	return m_name;
}

void User::setName(const std::string& name)
{
	m_name = name;
}

const std::string& User::getMail() const
{
	return m_mail;
}

void User::setMail(const std::string& mail)
{
	m_mail = mail;
}

const std::string& User::getPassword() const
{
	return m_password;
}

void User::setPassword(const std::string& password)
{
	m_password = password;
}

