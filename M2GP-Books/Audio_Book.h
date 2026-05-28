//
// Created by Lisa Dion on 1/17/22.
//

#ifndef POLYMORPHISM_AUDIO_BOOK_H
#define POLYMORPHISM_AUDIO_BOOK_H

#include "Book.h"

class Audio_Book : public Book {
private:
    string narrator;

public:
    // Constructors
    Audio_Book();
    Audio_Book(string title, string author, string ISBN, double price, int length, string narrator);
    Audio_Book(string title, vector<string> authors, string ISBN, double price, int length, string narrator);

    // Getter
    string get_narrator() const;
    string get_length_with_unit() const override;

    // Setter
    void set_narrator(string narrator);

    // Get info
    string get_info() const override;
};


#endif //POLYMORPHISM_AUDIO_BOOK_H
