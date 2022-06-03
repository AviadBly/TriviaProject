#pragma once
#include <iostream>
#include <vector>
using namespace std;


class Question
{
private:
	string m_question;
	vector<string> m_possibleAnswers;
public:
	Question() = default;
	Question(string question,string answer1, string answer2, string answer3, string answer4 );
	string getQuestion();
	vector<string> getPossibleAnswers();
	string getCorrectAnswer();
	void setQuestion(string question);
	void addPossibleAnswers(string answer);
	
};
