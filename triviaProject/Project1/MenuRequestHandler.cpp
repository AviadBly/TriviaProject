#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_statisticsManager(handlerFactory.getStatisticsManager()), m_roomManager(handlerFactory.getRoomManager())
{

}

bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	int code = requestInfo.code;
	return code == CREATE_ROOM_CODE || code == GET_ROOM_REQUEST || code == GET_PLAYERS_IN_ROOM_REQUEST_CODE || code == JOIN_ROOM_REQUEST_CODE || code == GET_STATISTICS_REQUEST_CODE || code == LOGOUT_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	
	try {
		switch (requestInfo.code) {
		case CREATE_ROOM_CODE:

		case GET_ROOM_REQUEST:
			getRooms(requestInfo);
		case GET_PLAYERS_IN_ROOM_REQUEST_CODE:
		case JOIN_ROOM_REQUEST_CODE:
		case GET_STATISTICS_REQUEST_CODE:
		case LOGOUT_REQUEST_CODE:
			std::cout << "hey";
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
	}
	

	return requestResult;
}

RequestResult MenuRequestHandler::logOut(RequestInfo requestInfo)
{
	return RequestResult();
	//this->m_handlerFactory.getLoginManger().logout();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
	GetRoomsResponse getRoomsResponse;
	RequestResult requestResult;
	
	getRoomsResponse.rooms = this->m_roomManager.getRooms();;
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomResponse(getRoomsResponse);
	
	return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{

	GetPlayersInRoomResponse getPlayersInRoomResponseRoomsResponse;
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	RequestResult requestResult;

	getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);

	
	for (auto i = m_roomManager.getRooms().begin(); i != m_roomManager.getRooms().end(); i++) {
	
		if (i->id == getPlayersInRoomRequest.roomId) {
			for (auto m = i->getAllUsers().begin(); m != i->getAllUsers().end(); m++)[
				getPlayersInRoomResponseRoomsResponse.players.push_back(*m);
			]
			
		}
		
	}

	requestResult.buffer = JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(getPlayersInRoomResponseRoomsResponse);
	
	return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
	JoinRoomRequest joinRoomRequest;
	joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;
	
	//to do: check if you the user can join room


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

	getHighScoreResponse.statistics = m_statisticsManager.getHighScore();

	requestResult.buffer = JsonResponsePacketSerializer::serializeHighScoreResponse(getHighScoreResponse);

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