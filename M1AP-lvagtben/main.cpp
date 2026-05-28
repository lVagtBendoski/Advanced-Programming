#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

char get_char_from_user();
string get_word_from_user();
string get_sentence_from_user();
int get_int_from_user();
double get_float_from_user();
bool char_in_str(char c, string& str);

int main() {
    cout << "Enter a single character:";
    char letter = get_char_from_user();
    cout << "You entered the character " << letter << endl;
    cout << "Please enter a word:";
    string word = get_word_from_user();
    cout << "You entered the word " << word << endl;
    cout << "Please enter a sentence:";
    string sentence = get_sentence_from_user();
    cout << "You entered the sentence: " << sentence << endl;
    cout << "Please enter an integer:";
    int num = get_int_from_user();
    cout << "You entered the number " << num << endl;
    cout << "Please enter a float:";
    double flo = get_float_from_user();
    cout << "You entered the floating-point number " << flo << endl;
    return 0;
}
bool char_in_string(char c, string& s) {
    for( char letter : s ) {
        if(letter == c) {
            return true;
        }
    }
    return false;
}

char get_char_from_user() {
    // TODO: Complete the function
    // NOTE: a char is not restricted to an alphabet letter
    string candidate;
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);
        if (candidate.length() > 1) {
            inputNotValid = true;
            cout << "Invalid input. Enter a single character:";
        }else if (candidate.empty()) {
            inputNotValid = true;
            cout << "No input. Enter a single character:";
        }
    }
    char c = candidate[0];
    return c;
}

string get_word_from_user() {
    // TODO: Complete the function
    string candidate;
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);

        if(char_in_string(' ', candidate)) {
            inputNotValid = true;
            cout << "Invalid input. Enter a single word:";
        }else if(candidate.empty()) {
            cout << "No input. Enter a single word:";
            inputNotValid = true;
        }
    }
    return candidate;
}

string get_sentence_from_user() {
    // TODO: Complete the function
    // NOTE: a sentence does NOT need punctuation or syntax validation
    string candidate = " ";
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);
        if(candidate.empty()) {
            cout << "No input. Enter a sentence:";
            inputNotValid = true;
        }
    }
    return candidate;
}

int get_int_from_user() {
    // TODO: Complete the function
    int num;
    string input;
    stringstream ss;
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, input);
        ss << input;
        if(char_in_string('.', input)){
            inputNotValid = true;
            cout << "Invalid input. Enter an integer not a floating point number:";
        }else if(input.empty()) {
            inputNotValid = true;
            cout << "No input. Enter an integer:";
        }else if(!(ss >> num)){
            inputNotValid = true;
            cout << "Invalid input. Enter an integer:";
        }
        ss.clear();
        ss.str("");
    }
    return num;
}

double get_float_from_user() {
    // TODO: Complete the function
    // NOTE: a float does not need to have a decimal part (meaning an integer is a valid float)
    double num;
    string input;
    stringstream ss;
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, input);
        ss << input;
        if(input.empty()) {
            inputNotValid = true;
            cout << "No input. Enter a float:";
        }else if(!(ss >> num)){
            inputNotValid = true;
            cout << "Invalid input. Enter a float:";
        }
        ss.clear();
        ss.str("");
    }
    return num;
}