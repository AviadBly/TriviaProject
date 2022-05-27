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
	string getQuestion();
	vector<string> getPossibleAnswers();
	string getCorrectAnswer();
};
