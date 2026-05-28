#include "Quiz.h"
#include <fstream>
using namespace std;
Quiz::Quiz() {

}
void Quiz::readQuizFromFile(string filename) {
    // TODO: Reset/clear the vector of Questions
    questions.clear();

    // Open the file
    ifstream inFile("../" + filename);

    // Read in the title and number of questions
    int numQuestions = 0;
    string newline;
    if (inFile) {
        getline(inFile, title);
        inFile >> numQuestions;
        getline(inFile, newline);
    }

    // Read in the questions
    int currQuestion = 0;
    Question q;
    string message = "";
    int number = 0;
    bool correct = false;
    while (inFile && currQuestion < numQuestions) {
        // Question Prompt
        getline(inFile, message);
        q.setPrompt(message);

        // Number of points
        inFile >> number;
        q.setPoints(number);

        // Clear Answers
        q.clearAnswers();

        // Number of answers
        inFile >> number;
        getline(inFile, newline);

        // Answers
        for (int i = 0; i < number; ++i) {
            // Read text
            getline(inFile, message);
            // Read correct
            inFile >> correct;
            getline(inFile, newline);
            // Add answer to question
            q.addAnswer(message, correct);
        }

        // TODO: Add the Question to vector field
        questions.push_back(q);

        // Increment question number
        ++currQuestion;
    }
    inFile.close();
}

// TODO: Implement the other methods of the Quiz class here



void Quiz::takeQuiz(string filename, ostream& outs, istream& ins) {
    // Read the quiz from the file
    readQuizFromFile(filename);

    // Reset fields
    totalPointsPossible = 0;
    totalPointsCorrect = 0;

    // Print title
    outs << title << endl << endl;

    string input;
    int index;
    // Print each question and get answer from user
    // TODO: the next line should loop through the vector field
    for (Question& q : questions) {
        totalPointsPossible += q.getPoints();

        // Print the question
        outs << q << endl;

        outs << "Your answer: ";
        getline(ins, input);
        // Input validation
        while (input.size() != 1 || tolower(input[0]) < 'a' || tolower(input[0]) >= ('a' + q.getNumAnswers())) {
            // TODO: There is invalid input.
            // Print "Invalid input. Try again: " to outs
            outs << "Invalid input, try again: ";
            // Use getline to read from ins into input
            getline(ins, input);
            // Note that with string/character invalid input, the stream stays in a good state so you do not need to
            // clear the stream or get rid of the junk input like you do with int/float type validation.

        }

        // Get the index of the answer based on the input from the user
        index = tolower(input[0]) - 'a';
        if (q.isCorrect(index)) {
            totalPointsCorrect += q.getPoints();
            outs << "Correct!" << endl << endl;
        } else {
            outs << "Incorrect" << endl << endl;
        }
    }

    outs << "You scored " << totalPointsCorrect;
    outs << " out of " << totalPointsPossible << endl;
}
string Quiz::getTitle() const{
    return title;
}

int Quiz::getTotalPointsCorrect() const {
    return totalPointsCorrect;
}

int Quiz::getTotalPointsPossible() const {
    return totalPointsPossible;
}

int Quiz::getNumberOfQuestions() const {
    return questions.size();
}

Question Quiz::getQuestion(int index) const {
    return questions[index];
}

Question Quiz::getQuestion(string prompt) const {
    for (int i = 0; i < questions.size(); ++i) {
        if(questions[i].getPrompt() == prompt) {
            return questions[i];
        }
    }
    //if no question was found with the given prompt we return the first question in the vector
    return questions[0];
}

void Quiz::setTitle(string title) {
    this->title = title;
}

void Quiz::addQuestion(Question q) {
    questions.push_back(q);
}