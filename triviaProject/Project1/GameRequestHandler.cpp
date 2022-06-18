#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Game& game, const LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handleFactory) : m_gameManager(gameManager), m_handlerFactory(handleFactory), m_game(game)
{
	
	hasAddedStatsYet = false;
	m_user = user;
}


bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	unsigned int code = requestInfo.code;

	return code == LEAVE_GAME_REQUEST_CODE || code == GET_QUESTION_REQUEST_CODE ||
		code == SUBMIT_ANSWER_REQUEST_CODE || code == GET_GAME_RESULT_REQUEST_CODE;
}


RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
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
			requestResult = getGameResults();
			break;
		
		}

	}	
	catch (const ServerException& serverException) {
		m_gameManager.removeUser(m_user, m_game); // remove user from game
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


	if (m_game.hasPlayerFinishedGame(m_user)) {
		getQuestionResponse.status = getQuestionResponse.noMoreQuestionStatus;
		
	}
	else {
		Question userQuestion = m_game.getQuestionForUser(m_user);
		getQuestionResponse.status = getQuestionResponse.status_ok;
		getQuestionResponse.question = userQuestion.getQuestionString();
		getQuestionResponse.answers = userQuestion.getPossibleAnswers();
	}
	
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetQuestionResponse(getQuestionResponse);
	
	time(&sendingTime);		//sendingTime = current time

	return requestResult;
}


RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	const double ALLOWED_DELAYED_TIME = 1.5; //in seconds

	double answerTime = difftime(requestInfo.receivalTime, sendingTime);

	if (answerTime > ALLOWED_DELAYED_TIME + m_game.getTimePerQuestion()){
		throw ServerException(ERROR_MSG_USER_DELAY, ServerException::ACTIVELY_DISCONECT_USER_CODE);	//disconnect from user
	}

	if (answerTime > m_game.getTimePerQuestion()) {
		answerTime = m_game.getTimePerQuestion();
	}
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
	
	if (m_game.hasPlayerFinishedGame(m_user)) {
		getGameResultsResponse.status = getGameResultsResponse.status_ok;
		getGameResultsResponse.results = m_game.getGameResults();

		if (!hasAddedStatsYet) {
			
			hasAddedStatsYet = true;
			addStatistics();
		}

	}
	else { //if game has not ended yet
		getGameResultsResponse.status = getGameResultsResponse.noResultsStatus;		
	}
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetGameResultsResponse(getGameResultsResponse);


	return requestResult;
}

void GameRequestHandler::addStatistics()
{
	StatsUser oldUserStats = m_handlerFactory.getStatisticsManager().getStatsUser(m_user.getName());

	StatsUser newUserStats = m_game.getCurrectStatisticsOnUser(m_user);

	oldUserStats.setGames(oldUserStats.getGames() + newUserStats.getGames());
	oldUserStats.setCorrect(oldUserStats.getCorrect() + newUserStats.getCorrect());
	oldUserStats.setTime(newUserStats.getNewAverage(oldUserStats, newUserStats.getTotalAnswers(), newUserStats.getTime()));
	oldUserStats.setTotalAnswers(oldUserStats.getTotalAnswers() + newUserStats.getTotalAnswers());


	m_handlerFactory.getStatisticsManager().insertStats(oldUserStats);
}
