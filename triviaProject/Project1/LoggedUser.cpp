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

void StatsUser::setName(std::string name)
{
	m_name = name;
}

void StatsUser::setTime(double time)
{
	m_time = time;
}

void StatsUser::setCorrect(int correct)
{
	m_correct = correct;
}

void StatsUser::setTotal(int total)
{
	m_total = total;
}

void StatsUser::setGames(int games)
{
	m_games = games;
}

const std::string& StatsUser::getName() const
{
	return m_name;
}
const int StatsUser::getCorrect()
{
	return m_correct;
}

const int StatsUser::getTotal()
{
	return m_total;
}
const int StatsUser::getGames()
{
	return m_games;
}

const double StatsUser::getTime()
{
	return m_time;
}