#include "Library.h"

Library::Library() {
	visitors_counter = 0;
	visitors = nullptr;

	size = 10;
	books = new Book * [size];
	books[0] = new Book("The Catcher in the Rye", "J.D. Salinger", "Fiction");
	books[1] = new Book("1984", "George Orwell", "Dystopian");
	books[2] = new Book("To Kill a Mockingbird", "Harper Lee", "Fiction");
	books[3] = new Book("Moby Dick", "Herman Melville", "Adventure");
	books[4] = new Book("The Great Gatsby", "F. Scott Fitzgerald", "Fiction");
	books[5] = new Book("War and Peace", "Leo Tolstoy", "Historical Fiction");
	books[6] = new Book("Pride and Prejudice", "Jane Austen", "Romance");
	books[7] = new Book("The Lord of the Rings", "J.R.R. Tolkien", "Fantasy");
	books[8] = new Book("The Brothers Karamazov", "Fyodor Dostoevsky", "Philosophical Fiction");
	books[9] = new Book("Brave New World", "Aldous Huxley", "Dystopian");
}

Library::Library(const Library& other) {
	size = other.size;
	books = new Book * [size];
	for (int i = 0; i < size; i++) {
		books[i] = new Book(*other.books[i]);
	}

	visitors_counter = other.visitors_counter;
	visitors = new Visitor * [visitors_counter];
	for (int i = 0; i < visitors_counter; i++) {
		visitors[i] = new Visitor(*other.visitors[i]);
	}
}

Library::~Library() {
	delete[] books;
	delete[] visitors;
}

void Library::add_book(Book& book) {
	int new_size = size + 1;
	Book** temp = new Book * [new_size];

	for (int i = 0; i < size; ++i) {
		temp[i] = books[i];
	}
	temp[size] = new Book(book);
	delete[] books;
	books = temp;
	size++;
}

void Library::show() {
	for (int i = 0; i < size; ++i) {
		if (books[i] != nullptr) {
			std::cout <<
				books[i]->getName() << ' ' <<
				books[i]->getAuthor() << ' ' <<
				books[i]->getGenre() << '\n';
		}
	}
}

Book* Library::findByName(const char* name) {
	for (int i = 0; i < size; ++i) {
		if (strcmp(books[i]->getName(), name) == 0) {
			return books[i];
		}
	}
	return nullptr;
}

Book* Library::findByAuthor(const char* author)
{
	for (int i = 0; i < size; ++i) {
		if (books[i] != nullptr && strcmp(books[i]->getAuthor(), author) == 0) {
			return books[i];
		}
	}
	return nullptr;
}

Book* Library::findByGenre(const char* genre)
{
	std::cout << "Library::findByGenre\tSTART\n";
	for (int i = 0; i < size; ++i) {
		if (strcmp(books[i]->getGenre(), genre) == 0) {
			return books[i];
		}
	}
	std::cout << "Library::findByGenre\tEND\n";
	return nullptr;
}

void Library::registration(Visitor& visitor) {
	int new_size = visitors_counter + 1;
	Visitor** temp = new Visitor * [new_size];

	for (int i = 0; i < visitors_counter; ++i) {
		temp[i] = visitors[i];
	}
	temp[visitors_counter] = &visitor;
	if (visitors != nullptr) {
		delete[] visitors;
	}
	visitors = temp;
	visitors_counter++;
	visitor.setId(visitors_counter);
}

void Library::takeBook(const char* name, Visitor* visitor) {
	Book* book = findByName(name);
	if (book == nullptr) { std::cerr << "Such book isn`t exists."; return; }

	if (book->is_in_stock() && visitor->getBooksNumber() < 3) {
		book->setStock(false);
		book->setOwner(visitor);

		visitor->addBook(book);
		visitor->upActivity();
		syncActivity(visitor);
		std::cout << "Happy reading!\n";
	}
	else if (!book->is_in_stock()) {
		std::cerr << "Book is not in stock\n";
		std::cout << book->getOwner()->getSurname() << " already owns this book.\n";
	}
	else if (visitor->getBooksNumber() >= 3) {
		std::cout << "You have exceeded your book limit.\n";
	}

}

void Library::returnBook(const char* name, Visitor* visitor)
{
	if (findByName(name) == nullptr) { std::cerr << "Such book isn`t exists.\n"; }
	if (findByName(name)->is_in_stock()) {
		std::cerr << "Book is already returned.\n";
		return;
	}
	Book* book = findByName(name);
	book->setStock(true);
	book->setOwner(nullptr);
	visitor->eraseBook(book);
	visitor->upActivity();
	syncActivity(visitor);
}

void Library::showByNames(const char* name) {
	for (int i = 0; i < size; ++i) {
		if (books[i] != nullptr && strcmp(books[i]->getName(), name) == 0) {
			std::cout <<
				books[i]->getName() << ' ' <<
				books[i]->getAuthor() << ' ' <<
				books[i]->getGenre() << '\n';
		}
	}
}

void Library::showByAuthor(const char* author)
{
	for (int i = 0; i < size; ++i) {
		if (books[i] != nullptr && strcmp(books[i]->getAuthor(), author) == 0) {
			std::cout <<
				books[i]->getName() << ' ' <<
				books[i]->getAuthor() << ' ' <<
				books[i]->getGenre() << '\n';
		}
	}
}

void Library::showByGenre(const char* genre) {
	for (int i = 0; i < size; ++i) {
		if (books[i] != nullptr && strcmp(books[i]->getGenre(), genre) == 0) {
			std::cout <<
				books[i]->getName() << ' ' <<
				books[i]->getAuthor() << ' ' <<
				books[i]->getGenre() << '\n';
		}
	}
}

void Library::syncActivity(Visitor* visitor) {
	for (int i = 0; i < visitors_counter; ++i) {
		if (visitors[i] != nullptr && visitors[i]->getSurname() == visitor->getSurname()) {
			visitors[i]->setActivity(visitor->getActivity());
			return;
		}
	}	
}

Visitor* Library::getActiveVisitor()
{
	int start = -1;
	Visitor* result = nullptr;
	for (int i = 0; i < visitors_counter; ++i) {
		if (visitors[i] != nullptr && visitors[i]->getActivity() > start) {
			result = visitors[i];
			start = visitors[i]->getActivity();
		}
	}
	return result;
}
