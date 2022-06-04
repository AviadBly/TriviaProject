#pragma once
#include <string>
#include <iostream>

class LoggedUser
{
public:

	LoggedUser(const std::string& name, const std::string& password);
	LoggedUser() = default;
	

	const std::string& getName() const;
	void setName(const std::string& name);

	const std::string& getPassword() const;
	void setPassword(const std::string& password);

	const std::string& getMail() const;
	void setMail(const std::string& mail);

	bool operator <(const LoggedUser& otherUser) const;

private:
	std::string m_password;
	std::string m_name;
	std::string m_mail;
};

class StatsUser
{
public:

	StatsUser(std::string name, double time, int correct, int total, int games)
	{
		m_name = name;
		m_time = time;
		m_correct = correct;
		m_total = total;
		m_games = games;
	}
	StatsUser() = default;

	void setName(std::string name);
	void setTime(double time);
	void setCorrect(int correct);
	void setTotal(int total);
	void setGames(int games);
	const std::string& getName() const;
	const int getCorrect();
	const int getTotal();
	const int getGames();
	const double getTime();
private:
	std::string m_name;
	double m_time;
	int m_correct;
	int m_total;
	int m_games;
};

