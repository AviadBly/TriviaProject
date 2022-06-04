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
	Game(vector<Question> questions, vector<User> users ,unsigned int id);
	Question getQuestionForUser(const User& user);
	
	unsigned int submitAnswer(User user, unsigned int answerId, float answerTime);

	bool removePlayer(User user);
	vector<PlayerResults> getGameResults();
	unsigned int getId() const;

	
private:
	unsigned int id;
	vector<Question> m_questions;
	map<User, GameData> m_players;
	unsigned int timePerQuestion;
	PlayerResults getPlayerResults(const User& user);
	float calculateNewAverageAnswerTime(float answerTime, const User& user);
};