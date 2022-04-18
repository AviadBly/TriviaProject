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

		case GET_PLAYERS_IN_ROOM_REQUEST_CODE:
		case JOIN_ROOM_REQUEST_CODE:
		case GET_STATISTICS_REQUEST_CODE:
		case LOGOUT_REQUEST_CODE:

		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
	}
	

	return requestResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
	GetRoomsResponse getRoomsResponse;
	RequestResult requestResult;
	std::vector<std::string> roomNames;
	//this->m_roomManager.getRooms()[0];
	//getRoomsResponse.rooms
	//requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomResponse()

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