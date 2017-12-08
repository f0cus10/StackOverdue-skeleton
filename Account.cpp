#include "Account.hpp"
//Overloaded Constructor
Account::Account(unsigned int id, string name){
  userID = id;
  username = name;
  borrowedBooksID.reserve(10);
  previousBorrows.reserve(10);
}
//Returns the ids of currently borrowedBooks
vector<unsigned int> Account::currentBorrowList() const{
  return borrowedBooksID;
}
//Returns the ids of previously borrowedBooks
vector<unsigned int> Account::previousBorrowList() const{
  return previousBorrows;
}
//Add a book to the list of currently borrowed books
void Account::checkout(unsigned int bookID){
  
}
//Return a book to the library and add it to the list of previous borrows
void Account::returnBook(unsigned int bookID);
//Returns true if the bookID exists in the borrowedBooksID
bool Account::bookBorrowed(unsigned int id);
