#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;


class Question
{


public:
	Question() = default;
	Question(const string& question,const string& answer1, const string& answer2, const string& answer3, const string& answer4);
	const string& getQuestionString() const;

	map<unsigned int, string> getPossibleAnswers();
	string getCorrectAnswer() const;	//the correct answer start with '*'

	int getIdOfAnswer(const string& answer) const;

	void setQuestion(const string& question);
	void addPossibleAnswers(const string& answer);
	void mixAnswers();

private:
	string m_question;
	map<unsigned int, string> m_possibleAnswers;
	
};
