#pragma once
#include <string>
<<<<<<< HEAD
#include <vector>
#include "Room.h"
=======
<<<<<<< HEAD
=======
#include <vector>
#include "Room.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71

struct Response {
	unsigned int status;
	const unsigned int status_ok = 2;
	const unsigned int status_error = 5;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse {
	std::string message;
};
=======
};

<<<<<<< HEAD
=======
struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse {
	std::string message;
};

>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
struct LogoutResponse : public Response {

};

struct GetRoomsResponse : public Response {
	std::vector<std::string> rooms;
<<<<<<< HEAD
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct getHighScoreResponse : public Response {
	std::vector<std::string> statistics;
};

=======
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct getHighScoreResponse : public Response {
	std::vector<std::string> statistics;
};

>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
struct getPersonalStatsResponse : public Response {
	std::vector<std::string> statistics;
};

struct JoinRoomResponse : public Response {

};

struct CreateRoomResponse : public Response {

<<<<<<< HEAD
};
=======
};
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
