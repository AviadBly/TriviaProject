#include "Users.h"
#include <iomanip>

unsigned int User::nextId;

//user
User::User(const string& name)
{
	m_name = name;
	m_id = nextId;
}

User::User()
{
	m_name = "";
	m_id = -1;
}

const unsigned int User::getId() const
{
	return 0;
}

const std::string& User::getName() const
{
	return m_name;
}

void User::setName(const std::string& name)
{
	m_name = name;
}

bool User::operator <(const User& otherUser) const
{
	return this->getId() < otherUser.getId();	//compares based on id												
}

bool User::operator ==(const User& otherUser) const
{
	return this->getId() == otherUser.getId();	//compares based on id												
}

//****************************************************** Logged user
LoggedUser::LoggedUser(const std::string& name, const std::string& password) :
	User(name), m_password(password)
{
	// Left empty
}

const std::string& LoggedUser::getMail() const
{
	return m_mail;
}

void LoggedUser::setMail(const std::string& mail)
{
	m_mail = mail;
}

bool LoggedUser::operator <(const LoggedUser& otherUser) const
{
	return this->getName().compare(otherUser.getName()) < 0;	//compares based on alphabetical order
														//returns true if this.name < otherUser.name
}

const std::string& LoggedUser::getPassword() const
{
	return m_password;
}

void LoggedUser::setPassword(const std::string& password)
{
	m_password = password;
}

//****************************************************** Stats User

void StatsUser::setName(const string& name)
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

bool StatsUser::operator <(const StatsUser& otherUser) const
{
	if (this->m_correct < otherUser.m_correct) {	
		return true;
	}
	else if (this->m_correct == otherUser.m_correct) {
		return this->m_time > otherUser.m_time;
	}

	return false;
}
