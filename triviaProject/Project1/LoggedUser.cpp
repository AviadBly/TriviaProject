#include "LoggedUser.h"
#include <iomanip>


LoggedUser::LoggedUser(const std::string& name, const std::string& password) :
	 m_name(name),m_password(password)
{
	// Left empty
}


const std::string& LoggedUser::getName() const
{
	return m_name;
}

void LoggedUser::setName(const std::string& name)
{
	m_name = name;
}

const std::string& LoggedUser::getMail() const
{
	return m_mail;
}

void LoggedUser::setMail(const std::string& mail)
{
	m_mail = mail;
}

const std::string& LoggedUser::getPassword() const
{
	return m_password;
}

void LoggedUser::setPassword(const std::string& password)
{
	m_password = password;
}

