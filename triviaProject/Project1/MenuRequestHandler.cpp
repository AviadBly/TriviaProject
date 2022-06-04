#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser newUser) : m_handlerFactory(handlerFactory), m_statisticsManager(handlerFactory.getStatisticsManager()), m_roomManager(handlerFactory.getRoomManager())
{
	
	this->m_user = newUser;
	//just for testing
	RoomData d;
	d.id = 1;
	d.maxPlayers = 5;
	d.name = "firstR";
	d.numOfQuestionsInGame = 6;
	d.timePerQuestion = 12;

	this->m_roomManager.createRoom(LoggedUser("sha", "123"), d);
	d.id = 2;
	d.name = "secondRoom";
	d.numOfQuestionsInGame = 11;
	d.timePerQuestion = 20;
	this->m_roomManager.createRoom(LoggedUser("gal", "568"), d);

}

bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	unsigned int code = requestInfo.code;
	return code == CREATE_ROOM_CODE || code == GET_ROOMS_REQUEST || code == GET_PLAYERS_IN_ROOM_REQUEST_CODE
		|| code == JOIN_ROOM_REQUEST_CODE || code == GET_PERSONAL_STATISTICS_REQUEST_CODE || code == LOGOUT_REQUEST_CODE
		|| code == GET_HIGH_SCORES_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	
	
	try {
		switch (requestInfo.code) {
		case CREATE_ROOM_CODE:
			requestResult =  createRoom(requestInfo);
			break;
		case GET_ROOMS_REQUEST:
			requestResult =  getRooms();
			break;
		case GET_PLAYERS_IN_ROOM_REQUEST_CODE:
			requestResult =  getPlayersInRoom(requestInfo);
			break;
		case JOIN_ROOM_REQUEST_CODE:
			requestResult = joinRoom(requestInfo);
			break;
		case GET_PERSONAL_STATISTICS_REQUEST_CODE:
			requestResult = getPersonalStatistics();
			break;
		case GET_HIGH_SCORES_REQUEST_CODE:
			requestResult = getHighScore();
			break;		
		case LOGOUT_REQUEST_CODE:
			requestResult = logOut();
			delete this;
			return requestResult;
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
	}
	
	if (requestResult.newHandler == nullptr) {
		requestResult.newHandler = this;
	}
	return requestResult;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo)
{
	CreateRoomRequest createRoomRequest;
	createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	RequestResult requestResult;
	CreateRoomResponse createRoomResponse;

	RoomData roomData;
	roomData.maxPlayers = createRoomRequest.maxUsers;
	roomData.name = createRoomRequest.roomName;
	roomData.timePerQuestion = createRoomRequest.answerTimeout;
	roomData.numOfQuestionsInGame = createRoomRequest.questionCount;
	roomData.isActive = false;


	unsigned int roomId = m_roomManager.createRoom(m_user, roomData);
	createRoomResponse.status = createRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeCreateRoomResponse(createRoomResponse);
	requestResult.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_roomManager.getSingleRoom(roomId));

	return requestResult;
}



RequestResult MenuRequestHandler::getRooms()
{
	GetRoomsResponse getRoomsResponse;
	RequestResult requestResult;
	
	getRoomsResponse.rooms = this->m_roomManager.getRooms();

	//***remove this later, its for tests***
	std::cout << "Rooms:\n";
	for (auto i = getRoomsResponse.rooms.begin(); i != getRoomsResponse.rooms.end(); i++) {
		std::cout << i->getData().name << ", ";
	}
	std::cout << "\n\n";
	

	getRoomsResponse.status = getRoomsResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomResponse(getRoomsResponse);
	

	return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{

	GetPlayersInRoomResponse getPlayersInRoomResponse;
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	RequestResult requestResult;

	getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);


	auto rooms = m_roomManager.getRooms();

	for (auto& i : rooms) {
	
		//finds the room with the given id
		if (i.getData().id == getPlayersInRoomRequest.roomId) {

			//add all the players
			auto allPlayers = i.getAllUsersNames();
			for (auto& p : allPlayers){
				getPlayersInRoomResponse.players.push_back(p);
			}		
		} 	
	}
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(getPlayersInRoomResponse);
	
	return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo)
{
	JoinRoomRequest joinRoomRequest;
	joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;
	
	joinRoomResponse.status = joinRoomResponse.status_error;
	Room wantedRoom;
	auto rooms = m_roomManager.getRooms();

	for (auto& i : rooms) {

		//finds the room with the given id, and checks if a new user can join
		if (i.getData().id == joinRoomRequest.roomId && i.canNewUserJoin()) {

			joinRoomResponse.status = joinRoomResponse.status_ok;
			wantedRoom = i;
			
			m_roomManager.addUserToRoom(i.getData().id, m_user);
			requestResult.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, wantedRoom);
			break;
		}
	}

	requestResult.buffer = JsonResponsePacketSerializer::serializeJoinRoomResponse(joinRoomResponse);
	
	return requestResult;
}



RequestResult MenuRequestHandler::getHighScore() const
{
	GetHighScoreResponse getHighScoreResponse;
	RequestResult requestResult;

	getHighScoreResponse.status = getHighScoreResponse.status_ok;
	getHighScoreResponse.statistics = m_statisticsManager.getHighScore();

	requestResult.buffer = JsonResponsePacketSerializer::serializeHighScoreResponse(getHighScoreResponse);

	return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStatistics() const
{
	GetPersonalStatsResponse getPersonalStatsResponse;
	RequestResult requestResult;

	getPersonalStatsResponse.status = getPersonalStatsResponse.status_ok;
	getPersonalStatsResponse.statistics = m_statisticsManager.getUserStatistics(m_user.getName());

	requestResult.buffer = JsonResponsePacketSerializer::serializePersonalStatisticsResponse(getPersonalStatsResponse);

	return requestResult;
}

RequestResult MenuRequestHandler::logOut()
{
	LogoutResponse logoutResponse;

	RequestResult requestResult;

	logoutResponse.status = logoutResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeLogoutResponse(logoutResponse);
	requestResult.newHandler = m_handlerFactory.createLoginRequestHandler();

	return requestResult;
}