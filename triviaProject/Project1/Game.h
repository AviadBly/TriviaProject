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
	
	//not sure what these function should return
	Question getQuestionForUser(string user); //to do
	void submitAnswer(string user, string answer);
	void removePlayer(string user);

private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};