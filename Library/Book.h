#pragma once
#include"Visitor.h"
#include<string>
#include<iostream>

class Book
{
public:
	Book() = default;
	Book(const char* name, const char* genre);
	Book(const char* name, const char* author, const char* genre);
	Book(const Book& other);
	~Book();

	//Getters
	char*    getName()   const { return name; }
	char*    getAuthor() const { return author; }
	char*    getGenre()  const { return genre; }
	Visitor* getOwner()  const { return owner; }

	void getData() const;
	void setStock(bool stock)       { in_stock = stock; }
	void setOwner(Visitor* visitor) { owner = visitor; }
	bool is_in_stock() const { return in_stock; }

private:
	char* name;
	char* author;
	char* genre;

	bool in_stock;  //true default
	Visitor* owner; //nullptr default
};

