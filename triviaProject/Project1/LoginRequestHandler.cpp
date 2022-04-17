#include "RequestInfo.h"
#include "LoginRequestHandler.h"
<<<<<<< HEAD
#include "Login_SignUp_Requests.h"
=======
#include "Requests.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f


LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory) : m_loginManager(loginManager) , m_handleFactory(handleFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.code == SIGN_UP_REQUEST_CODE || requestInfo.code == LOGIN_REQUEST_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	
	if (requestInfo.code == SIGN_UP_REQUEST_CODE) {	//signUp
		requestResult = signUp(requestInfo);
	}
	else if (requestInfo.code == LOGIN_REQUEST_CODE) {	//login
		requestResult = login(requestInfo);
	}
	
	return requestResult;
}

void LoginRequestHandler::loadErrorMsg(RequestResult& requestResult, std::string msg)
{
	std::cout << msg;
	ErrorResponse errorMsg;
	errorMsg.message = msg;
	requestResult.newHandler = nullptr;
	requestResult.buffer = JsonResponsePacketSerializer::serializeErrorResponse(errorMsg);

}

<<<<<<< HEAD

=======
//login and signup need some SOLID
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;
	LoginRequest loginRequest;

	
	try {
<<<<<<< HEAD
		loginRequest = JsonRequestPacketDeserializer::deserializeLoginResponse(requestResult.buffer);
=======
		loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestResult.buffer);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
	}
	catch (const std::exception& e) {	//if there was a problem with the json format, return error msg
		loadErrorMsg(requestResult, e.what());
		return requestResult;
	}

	LoginResponse loginResponse;

	try {
		this->m_loginManager.login(loginRequest.username, loginRequest.password);	//this throws an error if login failed
		
		requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler();
		loginResponse.status = loginResponse.status_ok;	//status ok
<<<<<<< HEAD
=======
		requestResult.buffer = JsonResponsePacketSerializer::serializeLoginResponse(loginResponse);
	
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
	}
	catch (const std::exception& e) {	//if the login faild, return error msg
		std::cout << e.what() << "\n";
		requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();
		loadErrorMsg(requestResult, e.what());

		loginResponse.status = loginResponse.status_error;	//status error
	}			

	requestResult.buffer = JsonResponsePacketSerializer::serializeLoginResponse(loginResponse);

	return requestResult;
}

RequestResult LoginRequestHandler::signUp(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;
	SignupRequest signUp;

	try {
<<<<<<< HEAD
		signUp = JsonRequestPacketDeserializer::deserializeSignUpResponse(requestResult.buffer);
=======
		signUp = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestResult.buffer);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
	}
	catch (const std::exception& e) {
		loadErrorMsg(requestResult, e.what());
		return requestResult;
	}
	
	SignUpResponse signUpResponse;
	try {
		this->m_loginManager.signup(signUp.username, signUp.password, signUp.email);	//successfull signUp
			
		requestResult.newHandler = this->m_handleFactory.createMenuRequestHandler();
		
		signUpResponse.status = signUpResponse.status_ok;
		requestResult.buffer = JsonResponsePacketSerializer::serializeSignupRequest(signUpResponse);
	}
	catch (const std::exception& e) {	//failed signUp, return error msg
		std::cout << e.what() << "\n";
		requestResult.newHandler = this->m_handleFactory.createLoginRequestHandler();
		loadErrorMsg(requestResult, e.what());

		signUpResponse.status = signUpResponse.status_error;
	}
	

	return requestResult;
}