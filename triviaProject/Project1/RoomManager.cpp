#include "RoomManager.h"
#include "MyException.h"

RoomManager::RoomManager()
{
	nextRoomId = 1;
}

//create room and return the id of the room created
unsigned int RoomManager::createRoom(LoggedUser user, RoomData data)
{
	data.id = nextRoomId;
	Room newRoom(data, user); //create the room
	
	m_rooms.insert(std::pair<unsigned int, Room>(nextRoomId, newRoom));
	nextRoomId++;
	return data.id;
}

Room RoomManager::getSingleRoom(int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			return it->second;
		}
	}
	
	return Room();
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
	return false;
	throw MyException("Error!: No such ID! ");
}

vector<Room> RoomManager::getRooms()
{
	vector<Room> newVector(0);
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		Room currRoom = it->second;
		newVector.push_back(currRoom);
	}

	return newVector;
}

void RoomManager::setRoomActive(int ID)
{
	m_rooms[ID].setIsActive(true);
}

