#include "Game.h"
#include "LoggedUser.h"

Game::Game(vector<Question> questions)
{
	this->m_players;
	this->m_questions = questions;
}
void Game::getQuestionForUser(LoggedUser user)
{
	int random = rand() % m_questions.size();
	Question sel_elem = m_questions[random];
	m_players[user].currentQuestion = sel_elem;
	
}

bool Game::submitAnswer(LoggedUser user, string answer)
{
	string correctAnswer = m_players[user].currentQuestion.getCorrectAnswer();
	if (correctAnswer.compare(answer) == 0)
	{
		m_players[user].correctAnswerCount++;
		//m_players[user].
		return true;
	}
	else
	{
		m_players[user].wrongAnswerCount++;
		//m_players[user].
		return false;
	}
}

bool Game::removePlayer(LoggedUser user)
{
	return m_players.erase(user);
	
}
