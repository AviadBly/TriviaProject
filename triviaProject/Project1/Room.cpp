#include "Room.h"
#include <iostream>
using namespace std;
void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
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

list<string> Room::getAllUsers() const
{
	list<string> newList;
	for (auto it = begin(m_users); it != std::end(m_users); ++it) {
		newList.push_back(it->getName());
	}
	return newList;

}

//returns true if the room isnt full and is active
bool Room::canNewUserJoin()
{
	return this->m_users.size() < this->m_metadata.maxPlayers && this->m_metadata.isActive;
}

RoomData Room::getData() const
{
	return this->m_metadata;
}
