#pragma once
#include <string>
#include <iostream>

using namespace std;

class User {

public:
	User(const string& name);
	User();

	const std::string& getName() const;
	void setName(const std::string& name);

	bool operator<(const User& otherUser) const;
	bool operator==(const User& otherUser) const;

	const unsigned int getId() const;
	

protected:
	static unsigned int nextId;
	string m_name;
	unsigned int m_id;
};

class LoggedUser : public User
{
public:

	LoggedUser(const std::string& name, const std::string& password);
	LoggedUser() = default;
	
	
	const std::string& getPassword() const;
	void setPassword(const std::string& password);

	const std::string& getMail() const;
	void setMail(const std::string& mail);

	bool operator <(const LoggedUser& otherUser) const;

private:
	std::string m_password;
	std::string m_mail;
};

class StatsUser : public User
{
public:

	StatsUser(const std::string& name, double time, int correct, int total, int games) : User(name)
	{
		m_time = time;
		m_correct = correct;
		m_total = total;
		m_games = games;
		
	}
	StatsUser() = default;

	void setName(const string& name);
	void setTime(double time);
	void setCorrect(int correct);
	void setTotalAnswers(int total);
	void setGames(int games);
	int getCorrect() const;
	int getTotalAnswers() const;
	int getGames() const;
	double getTime() const;
	 
	static double getNewAverage(const StatsUser& user, int numberOfAnswers, double otherAvg);

	bool operator <(const StatsUser& otherUser) const;

private:
	double m_time;
	int m_correct;
	int m_total;
	int m_games;
};

