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
	bool isActive;
};

class Room
{
public:
	Room(RoomData metadata, LoggedUser user);
	Room();
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<string> getAllUsers() const;
	RoomData getData() const;
	bool canNewUserJoin();

	
private:
	
	RoomData m_metadata;
	vector<LoggedUser> m_users;

};