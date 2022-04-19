#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include <list>
using namespace std;


struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
public:
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	list<string> getAllUsers() const;
	RoomData getData() const;
	bool canNewUserJoin();
private:
	
	RoomData m_metadata;
	vector<LoggedUser> m_users;

};