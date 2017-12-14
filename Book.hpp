#ifndef BOOK_HPP
#define BOOK_HPP
#include <iostream>
#include <string>
using namespace std;

class Book{
public:
  Book(unsigned int id, string title, string author, string gen = "", unsigned int score = 0);
  //If book have been renewed twice, returns false. Otherwise, renews books and returns true
  bool renew(unsigned int dueDate);
  //Returns the book to the library, that is, erases all borrower information
  void returnBook();
  
  //Returns dueDate;
  unsigned int dueDate() const {return due; }
  //Returns popularity score
  unsigned int popularityScore() const {return popScore; }
  //Returns status
  char availability() const {return status; }
  //Returns borrower id
  unsigned int borrower() const {return borrowerID; }
  unsigned int getID() const {return bookID; }
  string getTitle() const {return bookTitle; }
  string getAuthor() const {return bookAuthor; }
  string getGenre() const {return genre; }
  
  //Checkout the book
  //If available, checkout book and return true; else, false.
  bool checkout(unsigned int userID, unsigned int dueDate, bool raisePopularity);
  //Check if the book is equal to each other
  bool operator==(const Book& other);
  
private:
  //Book Information
  unsigned int bookID;
  string bookTitle;
  string bookAuthor;
  string genre;
  unsigned int popScore;
  //A == Available,B == Borrowed
  char status;
  //Borrower Information
  unsigned int borrowerID = 0;
  unsigned int due = 0;
  unsigned int renewed = 0;
};
#endif
