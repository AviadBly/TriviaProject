#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser newUser) : m_handlerFactory(handlerFactory), m_statisticsManager(handlerFactory.getStatisticsManager()), m_roomManager(handlerFactory.getRoomManager())
{
	
	this->m_user = newUser;
	//just for testing
	

}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	unsigned int code = requestInfo.code;
	return code == CREATE_ROOM_CODE || code == GET_ROOMS_REQUEST || code == GET_PLAYERS_IN_ROOM_REQUEST_CODE
		|| code == JOIN_ROOM_REQUEST_CODE || code == GET_PERSONAL_STATISTICS_REQUEST_CODE || code == LOGOUT_REQUEST_CODE
		|| code == GET_HIGH_SCORES_REQUEST_CODE||code==CREATE_QUESTION_REQUEST_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
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
			break;
		case CREATE_QUESTION_REQUEST_CODE:
			requestResult = CreateQuestion(requestInfo);
			break;
		}

	}
	catch (const ServerException& serverException) {
		
		throw serverException;
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


	Room room = m_roomManager.getSingleRoom(getPlayersInRoomRequest.roomId);
	
	//add all the players
	auto allPlayers = room.getAllUsersNames();
	for (auto& p : allPlayers) {
		getPlayersInRoomResponse.players.push_back(p);
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
	Room& wantedRoom = m_roomManager.getSingleRoom(joinRoomRequest.roomId);
	
	
	//checks if a new user can join
	if (!wantedRoom.canNewUserJoin()) {
		throw ServerException("Room is full", ServerException::ROOM_IS_FULL_CODE);
	}

	joinRoomResponse.status = joinRoomResponse.status_ok;
		
	wantedRoom.addUser(m_user);		
		
	requestResult.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, wantedRoom);	
	
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

RequestResult MenuRequestHandler::CreateQuestion(const RequestInfo& requestInfo)
{
	CreateQuestionResponse createQuestionResponse;
	CreateQuestionRequest createQuestionRequest;
	RequestResult requestResult;

	createQuestionRequest = JsonRequestPacketDeserializer::deserializeCreateQuestionRequest(requestInfo.buffer);


	if (m_statisticsManager.CreateQuestion(createQuestionRequest.question, createQuestionRequest.answer1, createQuestionRequest.answer2, createQuestionRequest.answer3, createQuestionRequest.correct))
	{
		createQuestionResponse.status = createQuestionResponse.status_ok;
	}
	else
	{
		createQuestionResponse.status = createQuestionResponse.status_error;
	}
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeCreateQuestionResponse(createQuestionResponse);

	return requestResult;
}