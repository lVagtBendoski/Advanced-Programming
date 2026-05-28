//
// Created by Lisa Dion on 1/17/22.
//

#include "Audio_Book.h"
#include <string>
using namespace std;

Audio_Book::Audio_Book() {
    title = "Gmorning, Gnight! Little Pep Talks for Me & You";
    author.clear();
    author.push_back("Lin-Manuel Miranda");
    ISBN = "978-1984854278";
    retail_price = 11.95;
    length = 46;
    narrator = "Lin-Manuel Miranda";
}

Audio_Book::Audio_Book(string title, string author, string ISBN, double price, int length, string narrator) : Book(title, author, ISBN, price, length), narrator(narrator) {
}

Audio_Book::Audio_Book(string title, vector<string> authors, string ISBN, double price, int length, string narrator) : Book(title, authors, ISBN, price, length), narrator(narrator) {
}

string Audio_Book::get_narrator() const {
    return narrator;
}

string Audio_Book::get_length_with_unit() const {
    return to_string(length) + " minutes";
}

void Audio_Book::set_narrator(string narrator) {
    this->narrator = narrator;
}

string Audio_Book::get_info() const {
    // Add to the info from the Book class
    string info = Book::get_info();
    info += "Narrator: " + narrator + "\n";
    return info;
}