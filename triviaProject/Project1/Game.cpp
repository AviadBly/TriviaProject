#include "Game.h"
#include "LoggedUser.h"

Game::Game(vector<Question> questions)
{
	this->m_players;
	this->m_questions = questions;
}
void Game::getQuestionForUser(string user)
map<unsigned int, string> Game::getQuestionForUser(string user)
{
	int random = rand() % m_questions.size();
	Question sel_elem = m_questions[random];
	
	
}

void Game::submitAnswer(string user, string answer)
{
	
}

void Game::removePlayer(string user)
{
}
