#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

class RoomAdminRequestHandler : public RoomMemberRequestHandler {

public:

	RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo requestInfo) const override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;

private:

};