#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"



struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int AvarageAnswerTime;
};


class Game
{

public:
	Game(vector<Question> questions);
	void getQuestionForUser(string user);
	void submitAnswer(string user, string answer);
	void removePlayer(string user);

private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};