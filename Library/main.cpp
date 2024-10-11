#include<iostream>
#include"Library.h"
#include"Book.h"
#include <cstring>
using namespace std;

void menu() {
	cout << "1) Show list of books.\n"
		<< "2) Show list of books by name.\n"
		<< "3) Show list of books by author.\n"
		<< "4) Show list of books by genre.\n"
		<< "5) Find book by name.\n"
		<< "6) Find book by author.\n"
		<< "7) Find book by genre.\n"
		<< "8) Take book.\n"
		<< "9) Return book.\n"
		<< "10) The Most Active Visitor.\n"
		<< "0) Leave the library.\n";
}

int main() {
	Library lib;

	Visitor other("func activity presentation");
	lib.registration(other);
	lib.takeBook("The Lord of the Rings", &other);
	cout << other.getActivity() << '\n';

	char surname[100];
	cout << "Enter your surname: ";
	cin.getline(surname, 100);

	Visitor me(surname);
	lib.registration(me);
	int ch = -1;
	char input[100];

	while (ch != 0) {
		menu();
		do {
			cin >> ch;
		} while (ch < 0 || ch > 10);
		switch (ch)
		{
		case 1:
			lib.show(); break;
		case 2:
			cout << "Enter the name: ";
			cin.ignore(); cin.getline(input, 100);
			lib.showByNames(input); break;
		case 3:
			cout << "Enter the author: ";
			cin.ignore(); cin.getline(input, 100);
			lib.showByAuthor(input); break;
		case 4:
			cout << "Enter the genre: ";
			cin.ignore(); cin.getline(input, 100);
			lib.showByGenre(input); break;
		case 5:
			cout << "Enter the name: ";
			cin.ignore(); cin.getline(input, 100);
			lib.findByName(input)->getData(); break;
		case 6:
			cout << "Enter the author: ";
			cin.ignore(); cin.getline(input, 100);
			lib.findByAuthor(input)->getData(); break;
		case 7:
			cout << "Enter the genre: ";
			cin.ignore(); cin.getline(input, 100);
			lib.findByGenre(input)->getData(); break;
		case 8:
			cout << "Enter the name of book: ";
			cin.ignore(); cin.getline(input, 100);
			lib.takeBook(input, &me); break;
		case 9:
			cout << "Enter the name of book: ";
			cin.ignore(); cin.getline(input, 100);
			lib.returnBook(input, &me); break;
		case 10:
			cout << lib.getActiveVisitor()->getSurname(); break;
		}
		cout << "\n";
	}
}


