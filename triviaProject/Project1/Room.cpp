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

void Room::addUser(LoggedUser user)
{
	if (canNewUserJoin()) {
		this->m_users.push_back(user);
	}
	
}

void Room::removeUser(LoggedUser user)
{
	for (auto iter = m_users.begin(); iter != m_users.end(); iter++)
	{
		if (iter->getName()==user.getName())
		{
			m_users.erase(iter);
			
		}
	}

	
}

vector<string> Room::getAllUsers() const
{
	vector<string> usersNames(0);
	for (auto iter = m_users.begin(); iter != m_users.end(); iter++)
	{
		usersNames.push_back(iter->getName());
	}

	return usersNames;

}

//returns true if the room isnt full and is active
bool Room::canNewUserJoin()
{
	return this->m_users.size() < this->m_metadata.maxPlayers; //&& !this->m_metadata.isActive;  maybe add this later
}

void Room::setIsActive(bool isActive)
{
	this->m_metadata.isActive = isActive;
}

RoomData Room::getData() const
{
	return this->m_metadata;
}
