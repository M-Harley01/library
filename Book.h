// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;  //Title of the book
    std::string author; //Author of the book
    std::string ISBN;   //isbn for the book
    bool available;     //Availability of the book

public:

    //book constructor to initialise the book
    Book(const std::string& title, const std::string& author, const std::string& ISBN);


    //Getters for the book
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getISBN() const;
    bool isAvailable() const;


    //setter funciton to update the books availability
    void setAvailable(bool status);
};

#endif // BOOK_H
