#pragma once
#include"Book.h"
#include <iostream>

class Library
{
public:
	Library();
	Library(const Library& other);
	~Library();

	void show();
	Book* findByName  (const char* name);
	Book* findByAuthor(const char* name);
	Book* findByGenre (const char* name);

	void registration(Visitor& visitor);

	void takeBook  (const char* name, Visitor* visitor);
	void returnBook(const char* name, Visitor* visitor);

	void showByNames (const char* name);
	void showByAuthor(const char* name);
	void showByGenre (const char* name);

	void syncActivity(Visitor* visitor);
	Visitor* getActiveVisitor();

private:
	void add_book(Book& book);

	Visitor** visitors;
	Book** books;
	int visitors_counter;
	int size;
};

