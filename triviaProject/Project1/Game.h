#pragma once
#include "Question.h"
#include <map>
#include "Users.h"
#include "Responses.h"



struct GameData
{
	GameData() {
		currentQuestion = Question();
		correctAnswerCount = 0;
		wrongAnswerCount = 0;
		averageAnswerTime = 0;
		hasPlayerFinished = false;
	}

	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;
	bool hasPlayerFinished;
};


class Game
{

public:
	Game();
	Game(const vector<Question>& questions, const vector<User>& users, unsigned int timePerQuestion, unsigned int id);
	Question getQuestionForUser(const User& user);
	
	unsigned int submitAnswer(const User& user, unsigned int answerId, double answerTime);
	vector<PlayerResults> getGameResults();
	bool removePlayer(const User& user);
	
	unsigned int getId() const;
	bool hasEnded() const;
	void setHasEnded(bool isEnded);

	bool hasPlayerFinishedGame(const User& user);

	unsigned int getTimePerQuestion() const;

	bool operator ==(const Game& otherGame);	//compare based on id

private:
	//static unsigned int nextGameId;

	unsigned int m_id;
	vector<Question> m_questions;
	map<User, GameData> m_players;
	unsigned int timePerQuestion;
	bool hasGameEnded;


	PlayerResults getPlayerResults(const User& user);
	double calculateNewAverageAnswerTime(double answerTime, const User& user);
	void CheckIfGameFinished();
};