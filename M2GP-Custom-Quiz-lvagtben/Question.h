#ifndef M2GP_CUSTOM_QUIZ_QUESTION_H
#define M2GP_CUSTOM_QUIZ_QUESTION_H

#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;

struct answer {
    string text;
    bool correct;
};

class Question {
private:
    string prompt;
    int points;
    vector<answer> answers;
public:
    /* Constructor */
    Question();

    /* Getters */
    string getPrompt() const;
    int getPoints() const;
    int getNumAnswers() const;

    /* Setters */
    void setPrompt(string prompt);
    void setPoints(int points);

    /* Add an answer to the question */
    void addAnswer(answer a);
    void addAnswer(string text, bool correct);

    /* Remove an answer either by vector index or text match
     * If multiple text matches, removes all instances      */
    bool removeAnswer(int index);
    bool removeAnswer(string text);

    /* Removes all answers */
    void clearAnswers();

    /* Return true if answer is correct
     * If multiple text matches,
     * returns true if at least one is correct   */
    bool isCorrect(int index);
    bool isCorrect(string text);

    /* Overloaded output operator */
    friend ostream& operator << (ostream& outs, const Question& q);
};


#endif //M2GP_CUSTOM_QUIZ_QUESTION_H
