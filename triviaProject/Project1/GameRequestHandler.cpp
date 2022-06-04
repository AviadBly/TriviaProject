#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(const vector<User>& users, const LoggedUser& user, GameManager& gameManager, RequestHandlerFactory& handleFactory) : m_gameManager(gameManager), m_handlerFactory(handleFactory)
{
	this->m_game = gameManager.createGame(users);
	this->m_user = user;
}


bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	unsigned int code = requestInfo.code;

	return code == LEAVE_GAME_REQUEST_CODE || code == GET_QUESTION_REQUEST_CODE ||
		code == SUBMIT_ANSWER_REQUEST_CODE || code == GET_GAME_RESULT_REQUEST_CODE;
}


RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;

	unsigned int code = requestInfo.code;

	try {
		switch (requestInfo.code) {
		case LEAVE_GAME_REQUEST_CODE:
			requestResult = leaveGame();
			break;
		case GET_QUESTION_REQUEST_CODE:
			requestResult = getQuestion();
			break;
		case SUBMIT_ANSWER_REQUEST_CODE:
			requestResult = submitAnswer(requestInfo);
			break;
		case GET_GAME_RESULT_REQUEST_CODE:

			break;
		
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


RequestResult GameRequestHandler::leaveGame()
{

	RequestResult requestResult;
	LeaveGameResponse leaveGameResponse;
	
	
	m_gameManager.removeUser(m_user, m_game);	//remove us from the game
	leaveGameResponse.status = leaveGameResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(leaveGameResponse);
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);  //go back to menu

	return requestResult;
}

RequestResult GameRequestHandler::getQuestion()
{

	RequestResult requestResult;
	GetQuestionResponse getQuestionResponse;

	getQuestionResponse.status = getQuestionResponse.status_ok;
	
	Question userQuestion = m_game.getQuestionForUser(m_user);
	getQuestionResponse.question = userQuestion.getQuestionString();
	
	getQuestionResponse.answers = userQuestion.getPossibleAnswers();
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(getQuestionResponse);
	
	time(&sendingTime);		//get the current time to sendingTime

	return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	float answerTime = difftime(sendingTime, requestInfo.receivalTime);
	std::cout << "Answer time:" << answerTime << "\n";

	RequestResult requestResult;
	SubmitAnswerResponse submitAnswerResponse;
	SubmitAnswerRequest submitAnswerRequest;

	submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
	
	submitAnswerResponse.status = submitAnswerResponse.status_ok;
	submitAnswerResponse.correctAnswerID = m_game.submitAnswer(m_user, submitAnswerRequest.answerId, answerTime);
	
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(submitAnswerResponse);

	

	return requestResult;
}

RequestResult GameRequestHandler::getGameResults()
{

	RequestResult requestResult;
	GetGameResultsResponse getGameResultsResponse;
	
	
	getGameResultsResponse.status = getGameResultsResponse.status_ok;

	getGameResultsResponse.results = m_game.getGameResults();
	//should later add here the:  player results


	requestResult.buffer = JsonResponsePacketSerializer::serializeGetGameResultsResponse(getGameResultsResponse);


	return requestResult;
}