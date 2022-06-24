#include "RoomManager.h"
#include "ServerException.h"

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

//gets room by ID
Room& RoomManager::getSingleRoom(unsigned int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			return it->second;
		}
	}
	
	throw ServerException("No room with the given id", ServerException::ACTIVELY_DISCONECT_USER_CODE);
}

//Check for correctness.
bool RoomManager::doesRoomExist(unsigned int ID) {

	
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			return true;
		}
	}
	return false;
}
//in case admin leaves or any other possible case.
void RoomManager::deleteRoom(int ID)
{
	
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{

			m_rooms.erase(it);
			break;
		}
	}
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

void RoomManager::addUserToRoom(int ID, LoggedUser user)
{
	m_rooms[ID].addUser(user);
}

//if a user leaves the room after he already joined.
void RoomManager::removeUser(User user, unsigned int roomId)
{
	for (auto r = m_rooms.begin(); r != m_rooms.end(); r++) {
		if (r->second.getData().id == roomId) {
			r->second.removeUser(user);
			return;
		}
		
	}
}

