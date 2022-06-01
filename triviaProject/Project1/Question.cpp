#include "Question.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::replace
#include <vector>       // std::vector

Question::Question(string question, string answer1, string answer2, string answer3, string answer4)
{
    this->m_question = question;
    this->m_possibleAnswers.push_back(answer1);
    this->m_possibleAnswers.push_back(answer2);
    this->m_possibleAnswers.push_back(answer3);
    this->m_possibleAnswers.push_back(answer4);
}

string Question::getQuestion()
{
    return this->m_question;
}

vector<string> Question::getPossibleAnswers()
{
    vector<string> temp = m_possibleAnswers;
    for (auto iter = temp.begin(); iter != temp.end(); iter++)
    {
        string currentString = *iter;
        if (currentString[0] == '*')
        {
            string newStr = currentString.substr(1);
            replace(temp.begin(), temp.end(), *iter, newStr);
            
        }
    }
    return temp;
}

string Question::getCorrectAnswer()
{
    for (auto iter = m_possibleAnswers.begin(); iter != m_possibleAnswers.end(); iter++)
    {
        string currentString = *iter;
        if (currentString[0]=='*')
        {
            string newStr = currentString.substr(1);
            return newStr;
        }
    }
    return("Error");
}

void Question::setQuestion(string question)
{
    this->m_question = question;
}

void Question::addPossibleAnswers(string answer)
{
    this->m_possibleAnswers.push_back(answer);
}
