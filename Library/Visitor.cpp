#include "Visitor.h"
#include "Book.h"

Visitor::Visitor(const char* surname) {
    this->surname = new char[strlen(surname) + 1];
    strcpy_s(this->surname, strlen(surname) + 1, surname);
    books_number = 0;
    books = nullptr;
    activity = 0;
}

Visitor::Visitor(const Visitor& other)
{
    activity = other.activity;
    id = other.id;
    
    int size_surname = strlen(other.surname);
    surname = new char[size_surname + 1];
    strcpy_s(surname, size_surname + 1, other.surname);

    books_number = other.books_number;
    books = new Book * [books_number];
    for (int i = 0; i < books_number; i++) {
        books[i] = new Book(*other.books[i]);
    }
}

Visitor::~Visitor()
{
    for (int i = 0; i < books_number; ++i) {
        if (books[i] != nullptr) {
            delete books[i];
        }
    }

    delete[] books;
    if (surname != nullptr) {
        delete[] surname;
    }

}

void Visitor::addBook(Book* book) {
    int new_size = books_number + 1;
    Book** temp = new Book * [new_size];

    for (int i = 0; i < new_size - 1; ++i) {
        temp[i] = books[i];
    }
    temp[books_number] = book;
    delete[] books;
    books = temp;
    books_number++;
}

void Visitor::eraseBook(Book* book) {
    if (books_number == 0 || books == nullptr) {
        std::cout << "Such book isn`t exists.\n";
        return;
    }

    int index = -1;
    for (int i = 0; i < books_number; ++i) {
        if (books[i] == book) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << "Such book wasn`t found.\n";
        return;
    }

    int new_size = books_number - 1;
    Book** temp = new Book * [new_size];
    for (int i = 0, j = 0; i < books_number; ++i) {
        if (i != index) {
            temp[j++] = books[i];
        }
    }
    delete[] books;
    books = temp;
    --books_number;
}
