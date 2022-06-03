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
	Game() = default;
	Game(vector<Question> questions,unsigned int id);
	void getQuestionForUser(LoggedUser user);
	bool submitAnswer(LoggedUser user, string answer);
	bool removePlayer(LoggedUser user);
	unsigned int getId();

private:
	unsigned int id;
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	unsigned int timePerQuestion;
};