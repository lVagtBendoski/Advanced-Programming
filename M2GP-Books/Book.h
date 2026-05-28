//
// Created by Lisa Dion on 1/17/22.
//

#ifndef POLYMORPHISM_BOOK_H
#define POLYMORPHISM_BOOK_H

#include <string>
#include <vector>
using std::string, std::vector;

class Book {
protected:
    // Book title (and subtitle, if any)
    string title;
    // Author(s) of the book
    vector<string> author;
    // ISBN number as string (may contain X and dashes)
    string ISBN;
    // Retail price in USD
    double retail_price;
    // Number of pages in the book
    int length;

public:
    // Constructors
    Book();
    Book(string title, string author, string ISBN, double price, int length);
    Book(string title, vector<string> authors, string ISBN, double price, int length);

    // Getters
    string get_title() const;
    // If multiple authors, returns the first
    string get_author() const;
    vector<string> get_authors() const;
    string get_ISBN() const;
    double get_retail_price() const;
    int get_length() const;
    virtual string get_length_with_unit() const;

    // Setters
    void set_title(string title);
    void set_author(string author);
    void set_authors(vector<string> authors);
    void set_ISBN(string ISBN);
    void set_retail_price(double price);
    void set_length(int length);

    // Get book's information
    virtual string get_info() const;
};


#endif //POLYMORPHISM_BOOK_H
