#include "RequestInfo.h"
#include "LoginRequestHandler.h"
#include "Requests.h"


LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory) : m_loginManager(loginManager) , m_handleFactory(handleFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return requestInfo.code == SIGN_UP_REQUEST_CODE || requestInfo.code == LOGIN_REQUEST_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	try {
		if (requestInfo.code == SIGN_UP_REQUEST_CODE) {	//signUp
			requestResult = signUp(requestInfo);
		}
		else if (requestInfo.code == LOGIN_REQUEST_CODE) {	//login
			requestResult = login(requestInfo);
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
	

bool LoginRequestHandler::isUsernameValid(string& username) {

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

bool LoginRequestHandler::isPasswordValid(string& password) {
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
RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	RequestResult requestResult;
	
	LoginRequest loginRequest;

	
	
	loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	

	LoginResponse loginResponse;

	this->m_loginManager.login(loginRequest.username, loginRequest.password);	//this throws an error if login failed
		
	LoggedUser loggeduser(loginRequest.username, loginRequest.password);
	//change the handler to the menu handler
	requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler(loggeduser); 

	loginResponse.status = loginResponse.status_ok;	//status ok
	requestResult.buffer = JsonResponsePacketSerializer::serializeLoginResponse(loginResponse);
	

	return requestResult;
}

RequestResult LoginRequestHandler::signUp(RequestInfo requestInfo)
{
	RequestResult requestResult;
	
	SignupRequest signUp;

	signUp = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
	
	
	SignUpResponse signUpResponse;
	
	if (!isUsernameValid(signUp.username)) {
		throw("Username is not valid");
	}
	if (!isPasswordValid(signUp.password)) {
		throw("Pasword is not valid");
	}

	this->m_loginManager.signup(signUp.username, signUp.password, signUp.email);	//successfull signUp
		
	LoggedUser loggeduser(signUp.username, signUp.password);

	requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler(loggeduser);
		
	signUpResponse.status = signUpResponse.status_ok;
	requestResult.buffer = JsonResponsePacketSerializer::serializeSignupRequest(signUpResponse);
	
	return requestResult;
}