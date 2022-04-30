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

list<string> Room::getAllUsers()
{
	list<string> newList;
	for (auto it = begin(m_users); it != std::end(m_users); ++it) {
		newList.push_back(it->getName());
	}
	return newList;

}

RoomData Room::getData()
{
	return this->m_metadata;
}
