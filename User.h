// User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    int userID;                                 //ID for a user
    std::string name;                           //Name for a user
    std::vector<std::string> borrowedBooks;     //Vector to store all of the books borrowed by a user

public:

    //Constructor to initialise user details
    User(int userID, const std::string& name);  

    //Getter function for a users ID
    int getUserID() const;

    //Getter for a users name
    const std::string& getName() const;

    //Getter for the list of books borrowed by a user 
    const std::vector<std::string>& getBorrowedBooks() const;

    //Function to borrow a book
    void borrowBook(const std::string& bookISBN);

    //Function to return a book
    void returnBook(const std::string& bookISBN);

    //Funciton to check if a user has borrowed a specific book
    bool hasBorrowedBook(const std::string& bookISBN) const;
};

#endif // USER_H
