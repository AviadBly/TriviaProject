#pragma once
#include <map>
#include <iostream>
#include "Room.h"
#include <vector>
using namespace std;

class RoomManager
{
public:
	void createRoom(LoggedUser user,RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<RoomData> getRooms();


private:
	map<int, Room> m_rooms;
};