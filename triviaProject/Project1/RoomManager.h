#pragma once
#include <map>
#include <iostream>
#include "Room.h"
#include <vector>
using namespace std;

class RoomManager
{
public:
	RoomManager();
	void createRoom(LoggedUser user,RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<RoomData> getRooms();


private:
<<<<<<< HEAD
	int nextRoomId;
=======
<<<<<<< HEAD
	static int nextRoomId;
=======
	int nextRoomId;
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	map<unsigned int, Room> m_rooms;
};