#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;


class Question
{


public:
	Question() = default;
	Question(string question,string answer1, string answer2, string answer3, string answer4);
	string getQuestionString();
	map<unsigned int, string> getPossibleAnswers();
	string getCorrectAnswer();	//the correct answer start with '*'

	int getIdOfAnswer(string answer);

	void setQuestion(string question);
	void addPossibleAnswers(string answer);
	void mixAnswers();

private:
	string m_question;
	map<unsigned int, string> m_possibleAnswers;
	
};
