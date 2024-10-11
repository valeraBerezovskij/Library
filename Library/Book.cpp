#include "Book.h"

Book::Book(const char* name, const char* genre) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);

	this->genre = new char[strlen(genre) + 1];
	strcpy_s(this->genre, strlen(genre) + 1, genre);

	in_stock = true;
	owner = nullptr;
	author = nullptr;
}

Book::Book(const char* name, const char* author, const char* genre)
	: Book(name, genre)
{
	this->author = new char[strlen(author) + 1];
	strcpy_s(this->author, strlen(author) + 1, author);

	in_stock = true;
	owner = nullptr;
}

Book::Book(const Book& other) {
	int size_name = strlen(other.name);
	name = new char[size_name + 1];
	strcpy_s(name, size_name + 1, other.name);

	if (other.author) {
		int size_author = strlen(other.author);
		author = new char[size_author + 1];
		strcpy_s(author, size_author + 1, other.author);
	}
	else {
		author = nullptr;
	}

	int size_genre = strlen(other.genre);
	genre = new char[size_genre + 1];
	strcpy_s(genre, size_genre + 1, other.genre);

	owner = nullptr;
	owner = other.owner;
	in_stock = other.in_stock;
}

Book::~Book() {
	delete[] name;
	delete[] author;
	delete[] genre;
}

void Book::getData() const
{
	std::cout << name << ' ' << author << ' ' << genre << '\n';
}
