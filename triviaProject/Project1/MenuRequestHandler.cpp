#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser newUser) : m_handlerFactory(handlerFactory), m_statisticsManager(handlerFactory.getStatisticsManager()), m_roomManager(handlerFactory.getRoomManager())
{
	this->m_user = newUser;
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	unsigned int code = requestInfo.code;
	return code == CREATE_ROOM_CODE || code == GET_ROOM_REQUEST || code == GET_PLAYERS_IN_ROOM_REQUEST_CODE
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
		case GET_ROOM_REQUEST:
			requestResult =  getRooms(requestInfo);
			break;
		case GET_PLAYERS_IN_ROOM_REQUEST_CODE:
			requestResult =  getPlayersInRoom(requestInfo);
			break;
		case JOIN_ROOM_REQUEST_CODE:
			requestResult = joinRoom(requestInfo);
			break;
		case GET_PERSONAL_STATISTICS_REQUEST_CODE:
			requestResult = getPersonalStatistics(requestInfo);
			break;
		case GET_HIGH_SCORES_REQUEST_CODE:
			requestResult = getHighScore(requestInfo);
			break;		
		case LOGOUT_REQUEST_CODE:
			requestResult = logOut(requestInfo);
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

RequestResult MenuRequestHandler::logOut(RequestInfo requestInfo)
{

	LogoutResponse logoutResponse;
	
	RequestResult requestResult;

	logoutResponse.status = logoutResponse.status_ok;
	requestResult.buffer = JsonResponsePacketSerializer::serializeLogoutResponse(logoutResponse);

	this->m_user = LoggedUser();

	requestResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	
	return requestResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
	GetRoomsResponse getRoomsResponse;
	RequestResult requestResult;
	
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

	getRoomsResponse.rooms = this->m_roomManager.getRooms();
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomResponse(getRoomsResponse);
	

	return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{

	GetPlayersInRoomResponse getPlayersInRoomResponse;
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	RequestResult requestResult;

	getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);

	auto rooms = m_roomManager.getRooms();

	for (auto i = rooms.begin(); i != rooms.end(); i++) {
	
		//finds the room with the given id
		if (i->getData().id == getPlayersInRoomRequest.roomId) {

			auto allPlayers = i->getAllUsers();
			for (auto m = allPlayers.begin(); m != allPlayers.end(); m++){
				getPlayersInRoomResponse.players.push_back(*m);
			}
			
		} 
	
	}

	requestResult.buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(getPlayersInRoomResponse);
	

	return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
	JoinRoomRequest joinRoomRequest;
	joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;
	
	joinRoomResponse.status = joinRoomResponse.status_error;
	
	auto rooms = m_roomManager.getRooms();
	for (auto i = rooms.begin(); i != rooms.end(); i++) {

		//finds the room with the given id
		if (i->getData().id && i->canNewUserJoin()) {

			joinRoomResponse.status = joinRoomResponse.status_ok;
			break;
		}

	}
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeJoinRoomResponse(joinRoomResponse);
	

	return requestResult;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo)
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

	
	m_roomManager.createRoom(this->m_user, roomData);
	createRoomResponse.status = createRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeCreateRoomResponse(createRoomResponse);
	

	return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo requestInfo)
{
	GetHighScoreResponse getHighScoreResponse;
	RequestResult requestResult;

	getHighScoreResponse.status = getHighScoreResponse.status_ok;
	getHighScoreResponse.statistics = m_statisticsManager.getHighScore();

	requestResult.buffer = JsonResponsePacketSerializer::serializeHighScoreResponse(getHighScoreResponse);

	return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStatistics(RequestInfo requestInfo)
{
	GetPersonalStatsResponse getPersonalStatsResponse;
	RequestResult requestResult;

	getPersonalStatsResponse.status = getPersonalStatsResponse.status_ok;
	getPersonalStatsResponse.statistics = m_statisticsManager.getUserStatistics(this->m_user.getName());

	requestResult.buffer = JsonResponsePacketSerializer::serializePersonalStatisticsResponse(getPersonalStatsResponse);

	return requestResult;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}