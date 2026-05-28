#include "Audio_Book.h"
#include <iostream>
#include <memory>
using namespace std;

int main() {
    cout << "----- Book -----" << endl;
    Book b;
    cout << b.get_info() << endl;

    cout << "----- Audio_Book -----" << endl;
    Audio_Book a;
    cout << a.get_info() << endl;

    cout << "----- vector of Books -----" << endl;
    vector<Book> books;
    books.push_back(Book());
    books.push_back(Audio_Book());
    for (Book& book : books) {
        cout << book.get_info() << endl;
    }

    cout << "----- vector of Book pointers -----" << endl;
    vector<unique_ptr<Book>> book_ptrs;
    book_ptrs.push_back(make_unique<Book>());
    book_ptrs.push_back(make_unique<Audio_Book>());
    for (unique_ptr<Book>& book_ptr : book_ptrs) {
        cout << book_ptr->get_info() << endl;
    }


    return 0;
}
