// Library.cpp
#include "Library.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to add a book to the library
void Library::addBook(const Book& book) {
    books.push_back(book);
}

//remove book function
void Library::removeBook(const std::string& title) {

    //boolean bookFound initialised to falce
    bool bookFound = false;

    //for loop that iterates through all books stored in the library
    for (size_t i = 0; i < books.size(); ++i) {

        /*if statement that states if the book at a certain point of 
        the loop equals the title passed into the function then erase
        the book. The boolean value is also set to true to show the book 
        has been found*/
        if (books[i].getTitle() == title) {
            books.erase(books.begin() + i);
            bookFound = true;
            break;
        }
    }

    //error handling for if the book is not found when the for loop is run

    if (!bookFound)
    {
        std::cout << "The title you entered could not be found." << endl;
    }
    
}


/*search by title function that functions similarly to the funtion
above. With key similarities being the use of a for loop so iterate
through book objects and a boolean value that helps to identify if 
the book is in the system or not*/

Book* Library::searchBookByTitle(const std::string& title) {
    bool titleFound = false;

    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getTitle() == title && books[i].isAvailable()) {
            titleFound = true;
            return &books[i];  
        }
    }

    if (!titleFound)
    {
        std::cout << "The title you entered could not be found." << endl;
    }
    
    
    return nullptr;  
}

/*another similar funtion to the two above. Again using a for loop to 
search through the books vecotr and displaying the books detail if the book 
is available*/


void Library::displayAvailableBooks() {
    for (size_t i = 0; i < books.size(); ++i) {
        const Book& book = books[i];
        if (book.isAvailable()) {
            std::cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << "\n";
        }
    }
}

//add user function that uses the push back fucntion to add a user object to the vector

void Library::addUser(const User& user) {
    users.push_back(user);
}


/*function to remove a user from the system. This function iterates through the user vector
and then checks if the users name matches that passed in as a parameter. It then
checks if the user has borrowed any books. If the user does have currently borrowed books
thn they are returned using the return book function. after this users are then removed
from the vector.*/
void Library::removeUser(const std::string& name) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getName() == name) {
            
            const auto& borrowedBooks = users[i].getBorrowedBooks();
            if (!borrowedBooks.empty()) {
                std::cout << "Returning borrowed books for user '" << name << "': ";
                for (const auto& ISBN : borrowedBooks) {
                    std::cout << ISBN << " ";
                    returnBook(users[i].getUserID(), ISBN);  
                }
                std::cout << "\n";
            }

            users.erase(users.begin() + i);
            std::cout << "User '" << name << "' removed successfully." << endl;
            return;
        }
    }
    std::cout << "User with name '" << name << "' not found." << endl;
}

/*Funciton to display all users in the library. It iterates through every user
in the function and retrieves information on books borrowed and if a book has been
borrowed it displays their isbn number. If the user has no books borrowed the funtion
will print this to the user.*/
void Library::displayAllUsers() {
    std::cout << "Users:\n";
    for (size_t i = 0; i < users.size(); ++i) {
        const auto& user = users[i];
        std::cout << "User ID: " << user.getUserID() << ", Name: " << user.getName() << "\n";

        const auto& borrowedBooks = user.getBorrowedBooks();
        if (!borrowedBooks.empty()) {
            std::cout << "  ISBN Numbers: ";
            for (size_t j = 0; j < borrowedBooks.size(); ++j) {
                std::cout << borrowedBooks[j] << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "  No books borrowed\n";
        }
    }
}


/*function to borrow a book. This function makes use of funcitons from #include <algorithm>
It finds the user withh the given ID in the users vector, it then finds the book with 
with the given isbn and checks if the book is actually available. The function
also checks if the user and book are found on the system. A success and error message are 
printed to the user also.*/
void Library::borrowBook(int userID, const std::string& bookISBN) {
    
    auto userIt = std::find_if(users.begin(), users.end(), [userID](const User& user) {
        return user.getUserID() == userID;
    });

    auto bookIt = std::find_if(books.begin(), books.end(), [bookISBN](const Book& book) {
        return book.getISBN() == bookISBN && book.isAvailable();
    });

    if (userIt != users.end() && bookIt != books.end()) {
        userIt->borrowBook(bookISBN);
        bookIt->setAvailable(false);
        std::cout << "Book borrowed successfully.\n";
    } else {
        std::cout << "Unable to borrow the book. Please check the user ID or book ISBN.\n";
    }
}

/*this funciton operates similarly to the one above, just calling on different functions
to return books instead of borrow them.*/
void Library::returnBook(int userID, const std::string& bookISBN) {
    auto userIt = std::find_if(users.begin(), users.end(), [userID](const User& user) {
        return user.getUserID() == userID;
    });

    auto bookIt = std::find_if(books.begin(), books.end(), [bookISBN](const Book& book) {
        return book.getISBN() == bookISBN && !book.isAvailable();
    });

    if (userIt != users.end() && bookIt != books.end()) {
        userIt->returnBook(bookISBN);
        bookIt->setAvailable(true);
        std::cout << "Book returned successfully.\n";
    } else {
        std::cout << "Unable to return the book. Please check the user ID or book ISBN.\n";
    }
}

/*Funciton to load all books from a file. It first opens the specified file from the parameter.
After this it checks to see if the file opened successfully. Book information is then
read from the file and a message is displayed to show details being loaded from the file.
A book object is created  with the details read from the file.*/
void Library::loadBooksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string ISBN, title, author;
        bool available;

        while (file >> ISBN >> std::quoted(title) >> std::quoted(author) >> available) {
            std::cout << "Loaded Book: ISBN=" << ISBN << ", title=" << title << ", author=" << author << ", available=" << available << "\n";
            Book book(title, author, ISBN);
            book.setAvailable(available);
            addBook(book);
        }
        file.close();
    } 
}

/*Function to load the users that operated in a similar fasion to the one above,
however this time reads in user related information.*/
void Library::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int userID;
        std::string name;
        std::string ISBN;

        while (file >> userID >> name) {
            User user(userID, name);

            std::getline(file >> std::ws, ISBN);
            std::istringstream iss(ISBN);
            for (std::string bookISBN; iss >> bookISBN;) {
                user.borrowBook(bookISBN);
            }

            addUser(user);  

            for (auto& book : books) {
                if (user.hasBorrowedBook(book.getISBN())) {
                    book.setAvailable(false);
                }
            }
        }

        file.close();
    } else {
        std::cerr << "Error opening user file: " << filename << "\n";
    }
}

/*Funtion to save the state of the file to two seperate files, one for books and one for users.
it opens up the user file name specified by the user and then writes user information to this file.*/
void Library::saveStateToFile(const std::string& booksFilename, const std::string& usersFilename) {

    std::ofstream usersFile(usersFilename);
    if (usersFile.is_open()) {
        for (const auto& user : users) {
            usersFile << user.getUserID() << " " << user.getName() << " ";

            const auto& borrowedBooks = user.getBorrowedBooks();
            for (const auto& ISBN : borrowedBooks) {
                usersFile << ISBN << " ";
            }

            usersFile << "\n";
        }
        usersFile.close();
    } else {
        std::cerr << "Error saving user information to file: " << usersFilename << "\n";
    }
}


