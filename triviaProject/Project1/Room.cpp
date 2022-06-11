#include "Room.h"
#include <iostream>
using namespace std;

Room::Room(RoomData metadata, LoggedUser user)
{
	this->m_metadata = metadata;
	this->m_users.push_back(user);
}

Room::Room()
{
	this->m_metadata.id = 0;
	this->m_metadata.isActive = 0;
	this->m_metadata.maxPlayers = 0;
	this->m_metadata.name = "";
	this->m_metadata.timePerQuestion = 0;
	this->m_metadata.numOfQuestionsInGame = 0;
}

void Room::addUser(const User& user)
{
	if (canNewUserJoin()) {
		this->m_users.push_back(user);
	}
	
}

void Room::removeUser(const User& user)
{
	for (auto iter = m_users.begin(); iter != m_users.end(); iter++)
	{
		if (iter->getName()==user.getName())
		{
			m_users.erase(iter);
			return;
		}
	}
	
}

vector<string> Room::getAllUsersNames() const
{
	vector<string> usersNames(0);
	for (auto iter = m_users.begin(); iter != m_users.end(); iter++)
	{
		usersNames.push_back(iter->getName());
	}

	return usersNames;

}
vector<User> Room::getAllUsers() const
{
	vector<User> users(0);
	for (auto iter = m_users.begin(); iter != m_users.end(); iter++)
	{
		users.push_back(*iter);
	}

	return users;
}

//returns true if the room isnt full and isnt active
bool Room::canNewUserJoin()
{
	return this->m_users.size() < this->m_metadata.maxPlayers && !(this->m_metadata.isActive);  
}

void Room::setIsActive(bool isActive)
{
	this->m_metadata.isActive = isActive;
}

RoomData Room::getData() const
{
	return this->m_metadata;
}
