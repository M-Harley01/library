// Library.h
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>

class Library {
private:
    std::vector<Book> books; //Storing books as a vector in the library
    std::vector<User> users; //Storing users as a vector in the library   

public:

    // Getter function for users
     const std::vector<User>& getUsers() const {
        return users;
    }

    // Function to add a book to the library
    void addBook(const Book& book);

    // Function to remove a book from the library by title
    void removeBook(const std::string& title);

    // Function to search for a book by title
    Book* searchBookByTitle(const std::string& title);

    // Function to display all available books in the library
    void displayAvailableBooks();

    // Function to add a user to the library
    void addUser(const User& user);

    // Function to remove a user from the library by name
    void removeUser(const std::string& title);

    // Function to display details of all users in the library
    void displayAllUsers();

    // Function to borrow a book by a user
    void borrowBook(int userID, const std::string& bookISBN);

    // Function to return a book by a user
    void returnBook(int userID, const std::string& bookISBN);

    // Function to load books from a file
    void loadBooksFromFile(const std::string& filename);

    // Function to load users from a file
    void loadUsersFromFile(const std::string& filename);

    // Function to save the current state of the library to files
    void saveStateToFile(const std::string& booksFilename, const std::string& usersFilename);
};

#endif // LIBRARY_H
