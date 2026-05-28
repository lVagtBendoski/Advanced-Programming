#ifndef M2GP_CUSTOM_QUIZ_QUIZ_H
#define M2GP_CUSTOM_QUIZ_QUIZ_H

#include "Question.h"
using std::istream;

class Quiz {
private:
    string title;
    int totalPointsCorrect;
    int totalPointsPossible;
    // TODO: Add component field to store the Question objects
    vector<Question> questions;
    /* Helper function to read Quiz data from a file */
    void readQuizFromFile(string filename);

public:
    /* Constructor */
    Quiz();

    /* Getters */
    string getTitle() const;
    int getTotalPointsCorrect() const;
    int getTotalPointsPossible() const;
    int getNumberOfQuestions() const;
    // Note: You may want to change the return type of the following two methods to optional<Question>
    Question getQuestion(int index) const;
    Question getQuestion(string prompt) const;

    /* Setter */
    void setTitle(string title);
    void addQuestion(Question newQuestion);

    /* Remove Question either by index or prompt */
    bool removeQuestion(int index);
    bool removeQuestion(string prompt);

    /* Interactive method to have the user take the Quiz */
    void takeQuiz(string filename, ostream& outs, istream& ins);
};


#endif //M2GP_CUSTOM_QUIZ_QUIZ_H
