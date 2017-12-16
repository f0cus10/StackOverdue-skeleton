#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include <unordered_map>
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
  void checkout(unsigned int bookID, string bookAuthor, string genre);
  //Return a book to the library and add it to the list of previous borrows
  void returnBook(unsigned int bookID);
  //If bookID is being borrowed in the current period, return true and modify index to the index of the book in the vector
  bool contains(unsigned int bookID, unsigned int& index, char period = 'C');
  
  string getName() const { return username; }
  unsigned int getID() const { return userID; }
  unsigned int getBorrowSize() const {return borrowedBooksID.size();}
  
  /*Recommendation getter */
  string getFavouriteGenre() const;
  string getSecondFavGenre()const ;
  string getFavouriteAuthor() const;
  
private:
  string username;
  unsigned int userID;
//  vector<const Book* const> borrowed;
//  vector<const Book* const> previousBorrow;
  vector<unsigned int> borrowedBooksID;
  vector<unsigned int> previousBorrows;
  /* recommendation data */
  unordered_map<string, unsigned int> favouriteGenre;
  unordered_map<string, unsigned int> favouriteAuthor;
  //Finds the most frequent item in the ordered list, does not take into account ignore
  string recommendSearch(const unordered_map<string, unsigned int>&, string ignore = "" ) const;
};
#endif
