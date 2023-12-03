#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#include "Book.h"
#include "User.h"
#include "Library.h"

using namespace std;

/*
Implementation of a tester file that allows all the
relevant functions to be tested
*/

int main() {

/*
creation of a library object within the tester 
funciton. This is only one instance of this class
and will be used to test all relevant functions 
partaining to the assignment
*/

    Library library;
    int choice = 0;

//while loop that ensures the menu continues to run unless option 13 is chosen

    while (choice != 13) { 
        cout << "Library menu." << endl;
        cout << "1) Display available books. " << endl;
        cout << "2) Display users. " << endl;
        cout << "3) Add a book to the library. " << endl;
        cout << "4) Remove a book from the library. " << endl;
        cout << "5) Search for a book by title. " << endl;
        cout << "6) Add a user to the system. " << endl;
        cout << "7) Remove a user from the system. " << endl;
        cout << "8) Load books from a file. " << endl;
        cout << "9) Load users from a file. " << endl;
        cout << "10) Save current state of library to file. " << endl;
        cout << "11) Borrow a book. " << endl;
        cout << "12) Return a book. " << endl;
        cout << "13) Exit. " << endl;

        cin >> choice;

        //error handling for any inputs outwith the menu options

        while (choice < 1 || choice > 13) {
            cout << "Invalid input" << endl;
            cout << "Input your choice again: ";
            cin >> choice;
        }

        //switch case statements to implement different menu options

        switch (choice) {

            /*Implementation of displaying all available books.
            This case statement simply calls the displayAvailableBooks()
            using the library object.*/

            case 1:{
                cout << "Available books:" << endl;
                library.displayAvailableBooks();
                break;}

            /*Implementation of displaying all available users.
            This case statement works identically to the one above
            but this time calls available users*/

            case 2:{

                cout << "Displaying all users:" << endl;
                library.displayAllUsers();
                break;}

            /*Implementation of adding a book object to the library.
            It allows the user to enter the relevent parameters required
            for the function. It also loops until the user decides they have
            no more books to add.*/

            case 3: {
                cout << "Add book has been selected" << endl;

                char addMoreBooks;
                do {
                    string title;
                    string author;
                    string isbn;

                    cout << "Enter the title of the book: ";
                    cin.ignore(); 
                    getline(cin, title);

                    cout << "Enter the author's name: ";
                    getline(cin, author);

                    cout << "Enter the ISBN number: ";
                    getline(cin, isbn);

                    Book newBook(title, author, isbn);

                    library.addBook(newBook);

                    cout << "Do you want to add another book? (y/n): ";
                    cin >> addMoreBooks;

                } while (addMoreBooks == 'y' || addMoreBooks == 'Y');

                break;
            }

            /*Implementation of removing a book object to the library.
            It functions very similar to the case statement above, however
            this time calls the remove book function.*/

            case 4: {
                cout << "Remove a book has been selected" << endl;

                char removeMoreBooks;
                do {
                    string title;

                    cout << "Enter the title of the book to remove: ";
                    cin.ignore(); 
                    getline(cin, title);
                    
                    library.removeBook(title);

                    cout << "Do you want to remove another book? (y/n): ";
                    cin >> removeMoreBooks;

                } while (removeMoreBooks == 'y' || removeMoreBooks == 'Y');

                break;
            }
            
            /*Implementation of searching for a book. Again this funciton
            gathers relevant parameters and then searches for the book by
            calling the search by title function. After doing this the title
            author and isbn are then displayed to the user*/

            case 5:{

                string title;
                cout << "enter the name of the book you want to search for" << endl;
                cin.ignore();
                getline(cin, title);

                Book* bookSearchedFor = library.searchBookByTitle(title);

                if(bookSearchedFor != nullptr){
                    cout << "Book details" << endl;

                    cout << "Title: " << bookSearchedFor->getTitle() << endl;
                    cout << "Author:" << bookSearchedFor->getAuthor() << endl;
                    cout << "ISBN: " << bookSearchedFor->getISBN() << endl;   
                }
                
                break;
            }

            /*Add user method*/

            case 6:{

                cout << "Add a user has been selected" << endl;

                char addMore;
                do {
                    string name;
                    int ID;
                    vector<string> booksBorrowed;

                    cout << "Enter the name of the user: " << endl;
                    cin.ignore(); 
                    getline(cin, name);
                    
                    cout << "Enter the users ID: " << endl;
                    cin >> ID;

                    char addBook;
                    do{
                        string bookTitle;
                        cout << "Enter a book borrowed by the user (or press 'n' if the user has no borrowed books): " << endl;
                        cin.ignore();
                        getline(cin, bookTitle);
                        booksBorrowed.push_back(bookTitle);

                        cout << "Does the user have any other books borrowed? " << endl;
                        cin >> addBook;
                    }while(addBook == 'y' || addBook == 'Y');
                    
                    User newUser(ID,name);
                    for (const string& book : booksBorrowed)
                    {
                        newUser.borrowBook(book);
                    }
                    
                    library.addUser(newUser);

                    cout << "Do you want to add another user? " << endl;
                    cin >> addMore;

                } while (addMore == 'y' || addMore == 'Y');

                break;
            }


            /*This is the remove user case. It gathers information from the user
            that it then uses as parameters for the remove user function*/

            case 7: {

                cout << "Remove a user has been selected: " << endl;

                char removeMore;
                do{
                    string user;

                    cout << "Enter the name of the user you wish to remove: " << endl; 
                    cin.ignore();
                    getline(cin, user);

                    library.removeUser(user);

                    cout << "Do you want to remove another user? (y/n):" << endl;
                    cin >> removeMore;
                }while(removeMore == 'y' || removeMore == 'Y');

                break;
            }

            /*cases 8 to 12 remain generally the same however have differences 
            in what methods they will be calling.*/

            case 8: {
                string fileName;

                cout << "Enter the name of the file you wish to load books from: " << endl;
                cin.ignore();
                getline(cin, fileName);

                ifstream file(fileName);
                if (file.is_open()) {
                    library.loadBooksFromFile(fileName);
                    file.close();
                } else {
                    cout << "Error opening file: " << fileName << ". Make sure the file is located in the current folder." << endl;
                }

                break;
            }

            case 9: {
                string fileName;

                cout << "Enter the name of the file you want to add users from: " << endl;
                cin.ignore();
                getline(cin, fileName);

                ifstream file(fileName);
                if (file.is_open()){
                    library.loadUsersFromFile(fileName);
                    file.close();
                }else{
                    cout << "error opening file: " << fileName << ". Make sure the file is located in the current folder." << endl;
                }

                break;
            }

            case 10: {
                
                string booksFilename;
                string usersFilename;

                cout << "Enter the name of the file to save book inventory: ";
                cin >> booksFilename;

                cout << "Enter the name of the file to save user information: ";
                cin >> usersFilename;

                library.saveStateToFile(booksFilename, usersFilename);
                break;
            }

            case 11: {
                cout << "Borrow a book has been selected" << endl;

                int userID;
                string bookISBN;

                cout << "Enter your user ID: ";
                cin >> userID;

                cout << "Enter the ISBN of the book you want to borrow: ";
                cin.ignore();
                getline(cin, bookISBN);

                library.borrowBook(userID, bookISBN);

                break;
            }


            case 12: {
                cout << "Return a book has been selected" << endl;

                int userID;
                string bookISBN;

                cout << "Enter your user ID: ";
                cin >> userID;

                cout << "Enter the ISBN of the book you want to return: ";
                cin.ignore();
                getline(cin, bookISBN);

                library.returnBook(userID, bookISBN);

                break;
            }

            case 13:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
