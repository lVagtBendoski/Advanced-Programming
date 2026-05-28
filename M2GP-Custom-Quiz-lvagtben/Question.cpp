#include "Question.h"
#include <iostream>
using namespace std;

Question::Question() : prompt(""), points(0) {
    answers.clear();
}

string Question::getPrompt() const {
    return prompt;
}

int Question::getPoints() const {
    return points;
}

int Question::getNumAnswers() const {
    return answers.size();
}

void Question::setPrompt(string prompt) {
    this->prompt = prompt;
}

void Question::setPoints(int points) {
    this->points = points;
}

void Question::addAnswer(answer a) {
    answers.push_back(a);
}

void Question::addAnswer(string text, bool correct) {
    answers.push_back({text, correct});
}

bool Question::removeAnswer(int index) {
    if (index < 0 || index >= answers.size()) {
        return false;
    }
    answers.erase(answers.begin() + index);
    return true;
}

bool Question::removeAnswer(string text) {
    bool removed = false;
    for (int i = 0; i < answers.size(); ++i) {
        if (answers[i].text == text) {
            answers.erase(answers.begin() + i);
            --i;
            removed = true;
        }
    }
    return removed;
}

void Question::clearAnswers() {
    answers.clear();
}

bool Question::isCorrect(int index) {
    if (index < 0 || index >= answers.size()) {
        return false;
    }
    return answers[index].correct;
}

bool Question::isCorrect(string text) {
    for (answer &a : answers) {
        if (a.text == text && a.correct) {
            return true;
        }
    }
    return false;
}

ostream& operator << (ostream& outs, const Question& q) {
    outs << q.prompt << endl;
    // Print the answers with letter numbering (a. b. c. etc)
    char letter = 'a';
    for (const answer& a : q.answers) {
        outs << letter << ". " << a.text << endl;
        // Go to the next letter
        letter = char(int(letter) + 1);
    }
    return outs;
}