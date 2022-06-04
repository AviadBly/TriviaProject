#include "RequestInfo.h"
#include "LoginRequestHandler.h"
#include "Requests.h"


LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory) : m_loginManager(loginManager) , m_handleFactory(handleFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == SIGN_UP_REQUEST_CODE || requestInfo.code == LOGIN_REQUEST_CODE;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	try {
		switch (requestInfo.code) {

			case SIGN_UP_REQUEST_CODE: 	//signUp
				requestResult = signUp(requestInfo);
				break;
			case LOGIN_REQUEST_CODE:
				requestResult = login(requestInfo);	//login
				break;
		
		}		
	}
	catch (const std::exception& e) {	//if there was any error, return error msg
		loadErrorMsg(requestResult, e.what());
	}
	
	return requestResult;
}

void LoginRequestHandler::loadErrorMsg(RequestResult& requestResult, std::string msg)
{
	std::cout << msg << "\n";
	ErrorResponse errorMsg;
	errorMsg.message = msg;
	errorMsg.status = errorMsg.status_error;
	requestResult.newHandler = this;
	requestResult.buffer = JsonResponsePacketSerializer::serializeErrorResponse(errorMsg);

}
	

bool LoginRequestHandler::isUsernameValid(const string& username) {

	const unsigned int MIN_SIZE = 2;
	if (username.size() < MIN_SIZE) {	//sets min size for the username
		return false;
	}

	//only allows letters or numbers
	auto it = find_if_not(username.begin(), username.end(), ::isalnum);
	if (it != username.end()) {
		return false;
	}

	return true;
}

bool LoginRequestHandler::isPasswordValid(const string& password) {
	const unsigned int MIN_SIZE = 4;
	if (password.size() < MIN_SIZE) {	//sets min size for the passoword
		return false;
	}

	//only allows letters or numbers
	auto it = find_if_not(password.begin(), password.end(), ::isalnum);
	if (it != password.end()) {
		return false;
	}

	return true;
}


//login and signup need some SOLID
RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	LoginResponse loginResponse;

	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	

	this->m_loginManager.login(loginRequest.username, loginRequest.password);	//this throws an error if login failed
		
	LoggedUser loggeduser(loginRequest.username, loginRequest.password);
	//change the handler to the menu handler
	requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler(loggeduser); 

	loginResponse.status = loginResponse.status_ok;	//status ok
	requestResult.buffer = JsonResponsePacketSerializer::serializeLoginResponse(loginResponse);
	

	return requestResult;
}

RequestResult LoginRequestHandler::signUp(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	SignUpResponse signUpResponse;
	SignupRequest signUpRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
	
	
	if (!isUsernameValid(signUpRequest.username)) {
		throw("Username is not valid");
	}
	if (!isPasswordValid(signUpRequest.password)) {
		throw("Pasword is not valid");
	}

	m_loginManager.signup(signUpRequest.username, signUpRequest.password, signUpRequest.email);	//successfull signUp
		
	LoggedUser loggedUser(signUpRequest.username, signUpRequest.password);

	requestResult.newHandler = m_handleFactory.createMenuRequestHandler(loggedUser);	//go to menu
		
	signUpResponse.status = signUpResponse.status_ok;
	requestResult.buffer = JsonResponsePacketSerializer::serializeSignupRequest(signUpResponse);
	
	return requestResult;
}