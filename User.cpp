// User.cpp
#include "User.h"
#include <algorithm>

// Constructor to initialize user details
User::User(int userID, const std::string& name)
    : userID(userID), name(name) {}

// Getter function for user ID
int User::getUserID() const { return userID; }

// Getter function for user name
const std::string& User::getName() const { return name; }

// Getter function for the list of borrowed books
const std::vector<std::string>& User::getBorrowedBooks() const { return borrowedBooks; }

// Function to borrow a book
void User::borrowBook(const std::string& bookISBN) {
    borrowedBooks.push_back(bookISBN);
}

// Function to return a book
void User::returnBook(const std::string& bookISBN) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookISBN);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

// Function to check if the user has borrowed a specific book
bool User::hasBorrowedBook(const std::string& bookISBN) const {
    return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookISBN) != borrowedBooks.end();
}
