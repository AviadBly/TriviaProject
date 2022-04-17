#include "RoomManager.h"
#include "MyException.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	
}

void RoomManager::deleteRoom(int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			m_rooms.erase(it);
		}
	}
}

unsigned int RoomManager::getRoomState(int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			RoomData currData=it->second.getData();
			return currData.isActive;
		}
	}
	throw MyException("Error!: No such ID! ");
}

vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> newVector;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		RoomData currData=it->second.getData();
		newVector.push_back(currData);
	}
	return newVector;
}
