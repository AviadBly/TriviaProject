#include <iostream>     // std::cout
#include <algorithm>    // std::replace
#include <vector>       // std::vector
#include<time.h>
#include <map>
#include "Question.h"

Question::Question()
{
}

Question::Question(const string& question, const string& answer1, const string& answer2, const string& answer3, const string& answer4)
{
    this->m_question = question;
    this->m_possibleAnswers.insert(pair<unsigned int, string>(0, answer1));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(1, answer2));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(2, answer3));
    this->m_possibleAnswers.insert(pair<unsigned int, string>(3, answer4));
    setCorrectAnswer();
    mixAnswers();
}



const string& Question::getQuestionString() const
{
    return this->m_question;
}

//removes the identifcation sign * for an astethic reason.
map<unsigned int, string> Question::getPossibleAnswers()  const
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
    return temp;
}

string Question::getCorrectAnswer() const
{
    return m_correctAnswer;
}

//finds the answer by the text, and returns its id
int Question::getIdOfAnswer(const string& answer) const
{
    for (auto& i : m_possibleAnswers) {
        if (answer == i.second) {
            return i.first;
        }
    }

    return -1;
}

void Question::setQuestion(const string& question)
{
    this->m_question = question;
}

void Question::addPossibleAnswers(const string& answer)
{
    this->m_possibleAnswers.insert(  pair<unsigned int, string>(m_possibleAnswers.size(), answer)  );
    setCorrectAnswer();
}

void Question::setCorrectAnswer() {
    for (auto& p : m_possibleAnswers) {
        if (p.second[0] == '*'){
            m_correctAnswer = p.second.substr(1);
            m_possibleAnswers[p.first] = m_correctAnswer;
        }
    }
}

//changes the order of the answers
void Question::mixAnswers()
{
    map<unsigned int, string> orderedAnswers;

    map<unsigned int, string> answers = getPossibleAnswers();

    int number;
    int size = m_possibleAnswers.size();

    srand(time(NULL));
    number = rand() % size;
      
    for (int i = 0; i < size; i++) {
        orderedAnswers.insert(  pair<unsigned int, string>(  (number + i) % size, answers[i]));
    }

    m_possibleAnswers = orderedAnswers;
}
