#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include <vector>
#include <string>
#include "Book.hpp"
class Account{
public:
  //Overloaded Constructor
  Account(unsigned int id, string name);
  //Returns the number of books currently borrowed
  unsigned int borrowSize(){ return borrowedBooksID.size(); }
  //Returns the ids of currently borrowedBooks
  vector<unsigned int> currentBorrowList() const;
  //Returns the ids of previously borrowedBooks
  vector<unsigned int> previousBorrowList() const;
  //Add a book to the list of currently borrowed books
  void checkout(unsigned int bookID);
  //Return a book to the library and add it to the list of previous borrows
  void returnBook(unsigned int bookID);
  //Returns true if the bookID exists in the borrowedBooksID
  bool bookBorrowed(unsigned int id);
private:
  string username;
  unsigned int userID;
//  vector<const Book* const> borrowed;
//  vector<const Book* const> previousBorrow;
  vector<unsigned int> borrowedBooksID;
  vector<unsigned int> previousBorrows;
};
#endif
