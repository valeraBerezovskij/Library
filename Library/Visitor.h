#pragma once
#include<string>
#include<iostream>
class Book;

class Visitor
{
public:
	Visitor(const char* surname);
	Visitor(const Visitor& other);
	~Visitor();
	//Getters
	unsigned getId()          const { return id; }
	char*    getSurname()     const { return surname; }
	unsigned getBooksNumber() const { return books_number; }
	int      getActivity()    const { return activity; }



	//Setters
	void setId(unsigned id) { this->id = id; }
	void setActivity(int activity) { this->activity = activity; }


	void upActivity() { ++activity; }
	// just
	void eraseBook(Book* book);
	void addBook(Book* book);
private:

	int activity;
	char* surname;
	unsigned id;
	unsigned books_number;
	Book** books;
};

