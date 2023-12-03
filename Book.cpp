// Book.cpp
#include "Book.h"


//book constructor to initialise the book
Book::Book(const std::string& title, const std::string& author, const std::string& ISBN)
    : title(title), author(author), ISBN(ISBN), available(true) {}

//Getter function for the book title
const std::string& Book::getTitle() const { return title; }

//Getter function for the books author
const std::string& Book::getAuthor() const { return author; }

//Getter fucntion for the isbn number
const std::string& Book::getISBN() const { return ISBN; }

//Getter function for the availability of the book
bool Book::isAvailable() const { return available; }

//Setter function for updating a books availability status
void Book::setAvailable(bool status) { available = status; }
