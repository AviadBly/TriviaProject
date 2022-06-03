#include "Question.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::replace
#include <vector>       // std::vector
#include<time.h>
#include <map>

Question::Question(string question, string answer1, string answer2, string answer3, string answer4)
{
    this->m_question = question;
    this->m_possibleAnswers.insert(pair<unsigned int, string>(0, answer1));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(1, answer2));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(2, answer3));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(3, answer4));
    mixAnswers();
}

string Question::getQuestionString()
{
    return this->m_question;
}

map<unsigned int, string> Question::getPossibleAnswers()
{
    map<unsigned int, string> temp = m_possibleAnswers;

    //remove the '*' from the start of the correct answer
    for (auto iter = temp.begin(); iter != temp.end(); iter++)
    {
        if (iter->second[0] == '*')
        {            
            temp[iter->first] = iter->second.substr(1);
        }
    }
    return m_possibleAnswers;
}

string Question::getCorrectAnswer()
{
    for (auto iter = m_possibleAnswers.begin(); iter != m_possibleAnswers.end(); iter++)
    {
        string currentString = iter->second;
        if (currentString[0] == '*')    //remove the '*' from the start of the correct answer
        {
            string newStr = currentString.substr(1);
            return newStr;
        }
    }
    return("Error");
}

int Question::getIdOfAnswer(string answer)
{
    for (auto i = m_possibleAnswers.begin(); i != m_possibleAnswers.end(); i++) {
        if (answer == i->second) {
            return i->first;
        }
    }

    return -1;
}

void Question::setQuestion(string question)
{
    this->m_question = question;
}

void Question::addPossibleAnswers(string answer)
{
    this->m_possibleAnswers.insert(  pair<unsigned int, string> (m_possibleAnswers.size(), answer)   );
}

//changes the order of the answers
void Question::mixAnswers()
{
    map<unsigned int, string> orderedAnswers;

    map<unsigned int, string> answers = getPossibleAnswers();

    int number;
    int size = m_possibleAnswers.size();

    number = rand() % size;
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        orderedAnswers.insert(  pair<unsigned int, string>(  (number + i) % size, answers[i]));
    }

    m_possibleAnswers = orderedAnswers;
}
