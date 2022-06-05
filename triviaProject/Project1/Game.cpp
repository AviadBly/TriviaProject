#include "Game.h"


//unsigned int Game::nextGameId;

Game::Game()
{
	this->timePerQuestion = 0;
	this->hasGameEnded = false;
	this->m_id = -1;
}

Game::Game(const vector<Question>& questions, const vector<User>& users, unsigned int timePerQuestion, unsigned int id)
{
	//nextGameId++;

	GameData initGameData;	//initialize the map with users, and empty game data
	for(auto i = users.begin(); i != users.end(); i++) {
		m_players.insert(pair<User, GameData>(*i, initGameData));
	}
	
	this->timePerQuestion = timePerQuestion;
	this->m_questions = questions;
	this->m_id = id;
	this->hasGameEnded = false;
}

Question Game::getQuestionForUser(const User& user)
{
	/*int random = rand() % m_questions.size();
	Question sel_elem = m_questions[random];*/


	//the new question is given from the question vector based on the number of question answered
	Question newQuestion = m_questions[m_players[user].correctAnswerCount + m_players[user].wrongAnswerCount];
	m_players[user].currentQuestion = newQuestion;
	
	return newQuestion;
	
}

double Game::calculateNewAverageAnswerTime(double answerTime, const User& user){
	double newAnswerTime = m_players[user].averageAnswerTime;

	unsigned int numberOfAnswers = m_players[user].correctAnswerCount + m_players[user].wrongAnswerCount;

	newAnswerTime = newAnswerTime * numberOfAnswers;
	newAnswerTime += answerTime;

	newAnswerTime = newAnswerTime / (numberOfAnswers + 1);
	return newAnswerTime;
}

//returns the correct answer id
//also increases the count of the correct or wrongs answers
unsigned int Game::submitAnswer(const User& user, unsigned int answerId, double answerTime)
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

	if (m_players[user].wrongAnswerCount + m_players[user].correctAnswerCount == m_questions.size()) {
		this->setHasEnded(true);
	}
	
	int correctAnswerId = m_players[user].currentQuestion.getIdOfAnswer(correctAnswer);
	if (correctAnswerId == -1) {
		throw ("Error");
	}
	return correctAnswerId;
	
}

bool Game::removePlayer(const User& user)
{
	return m_players.erase(user);	//if succesfull returns true
}

PlayerResults Game::getPlayerResults(const User& user)
{
	PlayerResults playerResults;

	GameData userGameData = m_players[user];
	playerResults.averageAnswerCount = userGameData.averageAnswerTime;
	playerResults.correctAnswerCount = userGameData.correctAnswerCount;
	playerResults.wrongAnswerCount = userGameData.wrongAnswerCount;
	playerResults.username = user.getName();

	return playerResults;
}

vector<PlayerResults> Game::getGameResults()
{
	vector<PlayerResults> results;

	for (auto i = m_players.begin(); i != m_players.end(); i++) {
		results.push_back(getPlayerResults(i->first));
	}
	return results;
}

unsigned int Game::getId() const
{
	return this->m_id;
}

bool Game::hasEnded() const
{
	return this->hasGameEnded;
}

void Game::setHasEnded(bool isEnded)
{
	hasGameEnded = isEnded;
}

bool Game::operator==(const Game& otherGame)
{
	return this->m_id == otherGame.getId();
}
