#include "Quiz.h"
#include <iostream>
using namespace std;

int main() {
    Quiz q;
    q.takeQuiz("CustomQuizData.txt", cout, cin);
    return 0;
}