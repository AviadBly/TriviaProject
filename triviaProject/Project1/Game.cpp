#include "Game.h"
#include "LoggedUser.h"

Game::Game(vector<Question> questions, vector<LoggedUser> users, unsigned int id)
{
	
	
	GameData initGameData;	//initialize the map with users, and empty game data
	for(auto i = users.begin(); i != users.end(); i++){
		m_players.insert(pair<LoggedUser, GameData>(*i, initGameData));
	}

	this->m_questions = questions;
	this->id = id;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	/*int random = rand() % m_questions.size();
	Question sel_elem = m_questions[random];*/


	//the new question is given from the question vector based on the number of question answered
	Question newQuestion = m_questions[m_players[user].correctAnswerCount + m_players[user].wrongAnswerCount];
	m_players[user].currentQuestion = newQuestion;

	return newQuestion;
	
}

float Game::calculateNewAverageAnswerTime(float answerTime, LoggedUser user) {
	float newAnswerTime = m_players[user].averageAnswerTime;
	unsigned int numberOfAnswers = m_players[user].correctAnswerCount + m_players[user].wrongAnswerCount;

	newAnswerTime = newAnswerTime * numberOfAnswers;
	newAnswerTime += answerTime;

	newAnswerTime = newAnswerTime / (numberOfAnswers + 1);
}

//returns the correct answer id
//also increases the count of the correct or wrongs answers
unsigned int Game::submitAnswer(LoggedUser user, unsigned int answerId, float answerTime)
{
	m_players[user].averageAnswerTime = calculateNewAverageAnswerTime(answerTime, user);

	string correctAnswer = m_players[user].currentQuestion.getCorrectAnswer();
	string userAnswer = m_players[user].currentQuestion.getPossibleAnswers()[answerId];

	if (userAnswer == correctAnswer) {
		m_players[user].correctAnswerCount++;
	}
	else {
		m_players[user].wrongAnswerCount++;
	}
	
	int correctAnswerId = m_players[user].currentQuestion.getIdOfAnswer(correctAnswer);
	if (correctAnswerId == -1) {
		throw ("Error");
	}
	return correctAnswerId;
}



bool Game::removePlayer(LoggedUser user)
{
	return m_players.erase(user);	//if succesfull returns true
}

vector<PlayerResults> Game::getGameResults()
{
	vector<PlayerResults> results;

	for (auto i = m_players.begin(); i != m_players.end(); i++) {
		results.push_back(getPlayerResults(i->first));
	}

	return results;
}

PlayerResults Game::getPlayerResults(LoggedUser user)
{
	PlayerResults playerResults;
	GameData userGameData = m_players[user];
	playerResults.averageAnswerCount = userGameData.averageAnswerTime;
	playerResults.correctAnswerCount = userGameData.correctAnswerCount;
	playerResults.wrongAnswerCount = userGameData.wrongAnswerCount;
	playerResults.username = user.getName();
	return playerResults;
}

unsigned int Game::getId() const
{
	return this->id;
}
