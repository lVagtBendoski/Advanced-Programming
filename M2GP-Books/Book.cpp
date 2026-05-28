//
// Created by Lisa Dion on 1/17/22.
//

#include "Book.h"
#include <iomanip>
#include <sstream>
using namespace std;

Book::Book() {
    title = "Teaching Computational Thinking: An Integrative Approach for Middle and High School Learning";
    author.push_back("Maureen D. Neumann");
    author.push_back("Lisa Dion");
    ISBN = "978-0262045056";
    retail_price = 45.00;
    length = 200;
}

Book::Book(string title, string author, string ISBN, double price, int length) {
    this->title = title;
    this->author.push_back(author);
    this->ISBN = ISBN;
    retail_price = price;
    this->length = length;
}

Book::Book(string title, vector<string> authors, string ISBN, double price, int length) {
    this->title = title;
    for (string &a : authors) {
        this->author.push_back(a);
    }
    this->ISBN = ISBN;
    retail_price = price;
    this->length = length;
}

string Book::get_title() const {
    return title;
}

string Book::get_author() const {
    if (author.size() > 0) {
        return author[0];
    }
    return "Anonymous";
}

vector<string> Book::get_authors() const {
    return author;
}

string Book::get_ISBN() const {
    return ISBN;
}

double Book::get_retail_price() const {
    return retail_price;
}

int Book::get_length() const {
    return length;
}

string Book::get_length_with_unit() const {
    return to_string(length) + " pages";
}

void Book::set_title(string title) {
    this->title = title;
}

void Book::set_author(string author) {
    this->author.clear();
    this->author.push_back(author);
}

void Book::set_authors(vector<string> authors) {
    this->author.clear();
    for (string &a : authors) {
        this->author.push_back(a);
    }
}

void Book::set_ISBN(string ISBN) {
    this->ISBN = ISBN;
}

void Book::set_retail_price(double price) {
    retail_price = price;
}

void Book::set_length(int length) {
    this->length = length;
}

string Book::get_info() const {
    // Title
    string info = "Title: " + title + "\n";

    // Author(s)
    info += "Author(s): ";
    if (author.empty()) {
        info += "Anonymous";
    } else {
        info += author[0];
    }
    for (int i = 1; i < author.size(); ++i) {
        info += ", " + author[i];
    }
    info += "\n";

    // ISBN
    info += "ISBN: " + ISBN + "\n";

    // Price
    // Need to get the price to print to 2 decimal places
    // The way to do that is use a stringstream to enable
    // the use of output manipulations, then read from
    // the stringstream into a string variable
    stringstream ss;
    ss << fixed << setprecision(2) << retail_price;
    string price;
    ss >> price;
    info += "Price: $" + price + "\n";

    // Length
    info += "Length: " + get_length_with_unit() + "\n";

    return info;
}