#include <fstream>
#include <iostream>
using namespace std;

// Different OSs use different CLI commands to run Python
#ifdef _WIN32
// TODO: If your Windows machine runs Python in CLI with "python" instead of "py", update this line.
const string python = "python";
#else
// TODO: If your Mac/Linux machine runs Python in CLI with "python3" instead of "python", update this line.
const string python = "python";
#endif

/*
 * Prompts the user for a filename.
 * Allows the user to enter nothing to use the default pic (autumn.jpg).
 * If the file has extension jpg, jpeg, jpe, or png
 * and it exists in the project folder, return it.
 * Otherwise, return the default pic filename.
 */
string get_sentence_from_user();

string get_filename();

/*
 * Prints the main menu of options:
 * (a) flip, (b) mirror, (c) invert, or (d) exit
 */
void print_menu();

/*
 * Prompts the user for one of the options from the menu.
 * Validates input: makes sure the user enters exactly one character
 * and that it is one of the four valid options.
 * If it isn't valid, keep prompting for input until a valid option
 * is entered.
 */
char get_manip_choice();

char get_char_from_user();

int main() {
    cout << "Welcome to the image manipulator!" << endl;
    string filename = get_filename();
    cout << "Using file " << filename << "." << endl;
    print_menu();
    char choice = get_manip_choice();
    cout << "Processing. Go to Python program when it opens. May take a few seconds." << endl;
    string command;
    switch (choice) {
        // Use command-line arguments to pass the filename and manip to the Python file
        case 'a': command = python + " ../render.py " + filename + " flip";
            break;
        case 'b': command = python + " ../render.py " + filename + " mirror";
            break;
        case 'c': command = python + " ../render.py " + filename + " invert";
            break;
    }
    system(command.c_str());
    return 0;
}

string get_filename() {
    string result;
    cout << "Please enter a filename to open." << endl;
    result = get_sentence_from_user();
    ifstream f(result.c_str());
    if (f.good()) {
        f.close();
        return result;
    }else {
        f.close();
        result = "../" + result;
        ifstream newf(result.c_str());
        if (newf.good()) {
            newf.close();
            return result;
        }else{
            return "../autumn.jpg";
        }
    }

}


string get_sentence_from_user() {
    // NOTE: a sentence does NOT need punctuation or syntax validation
    string candidate = " ";
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);
        if(candidate.empty()) {
            cout << "No input";
            inputNotValid = true;
        }
    }
    return candidate;
}

void print_menu() {
    cout << "(a) flip, (b) mirror, (c) invert, or (d) exit" << endl;
}

char get_manip_choice() {
    char result;
    bool inputBad = true;
    while (inputBad) {
        cout << "Please enter a valid choice of manipulation." << endl;
        result = get_char_from_user();
        if(result == 'a' || result == 'b' || result == 'c' || result == 'd') {
            inputBad = false;
        }else {
            cout << "Valid choices are: ";
            print_menu();
        }
    }
    return result;
}

char get_char_from_user() {
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
