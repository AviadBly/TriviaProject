#include "RequestInfo.h"
#include "LoginRequestHandler.h"
#include "Responses.h"

LoginRequestHandler::LoginRequestHandler()
{
	this->m_handleFactory
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.code == SIGN_RESPONSE_CODE || requestInfo.code == LOGIN_RESPONSE_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;

	
	//adding IRequestHandler*
	requestResult.newHandler = this;
	
	return requestResult;
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;

	LoginResponse login = JsonRequestPacketDeserializer::deserializeLoginRequest(requestResult.buffer);
	if (login.status == OK_STATUS) {
		try {
			this->m_loginManager.login(login.username, login.password);	//successfull login
			MenuRequestHandler menu;
			requestResult.newHandler = &menu;
		}
		catch (const std::exception& e) {	//failed login
			std::cout << e.what() << "\n";
			requestResult.newHandler = this;			
		}			
	}
	else {
		requestResult.newHandler = nullptr;	//login error
	}
	
	return requestResult;
}

RequestResult LoginRequestHandler::signUp(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;
	
	SignUpResponse login = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestResult.buffer);
	if (login.status == OK_STATUS) {
		try {
			this->m_loginManager.signup(login.username, login.password, login.email);	//successfull signUp
			MenuRequestHandler menu;
			requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler();;
		}
		catch (const std::exception& e) {	//failed signUp
			std::cout << e.what() << "\n";
			requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();
		}
	}
	else {
		requestResult.newHandler = nullptr;	//signUp error
	}

	return requestResult;
}