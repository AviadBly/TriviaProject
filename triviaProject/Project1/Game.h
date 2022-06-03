#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"
#include "Responses.h"



struct GameData
{
	GameData() {
		currentQuestion = Question();
		correctAnswerCount = 0;
		wrongAnswerCount = 0;
		averageAnswerTime = 0;
	}
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};


class Game
{

public:
	Game() = default;
	Game(vector<Question> questions, vector<LoggedUser> users ,unsigned int id);
	Question getQuestionForUser(LoggedUser user);
	
	unsigned int submitAnswer(LoggedUser user, unsigned int answerId, float answerTime);

	bool removePlayer(LoggedUser user);
	vector<PlayerResults> getGameResults();
	unsigned int getId() const;


private:
	unsigned int id;
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	unsigned int timePerQuestion;
	PlayerResults getPlayerResults(LoggedUser user);
	float calculateNewAverageAnswerTime(float answerTime, LoggedUser user);
};