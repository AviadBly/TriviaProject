#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include <list>
using namespace std;


struct RoomData
{
	RoomData() {
		id = 0;
		name = "";
		maxPlayers = 0;
		numOfQuestionsInGame = 0;
		timePerQuestion = 0;
		isActive = false;
	}
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
	void addUser(const User& user);
	void removeUser(const User& user);
	vector<string> getAllUsersNames() const;
	vector<User> getAllUsers() const;
	RoomData getData() const;
	bool canNewUserJoin();
	void setIsActive(bool isActive);
	
private:
	
	RoomData m_metadata;
	vector<User> m_users;

};