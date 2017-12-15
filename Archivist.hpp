//
//  Archivist.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/14/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef Archivist_hpp
#define Archivist_hpp

#include <iostream>
#include <vector>
#include <string>
#include "Book.hpp"
#include "Account.hpp"

struct Archivist{
  //Probably made this way too complicated
  typedef bool(*bookComparator)(Book*&,Book*&);
  typedef bool(*accountComparator)( Account*&, Account*&);
  /* Book-related function */
  bookComparator bookSortSelector(string criteria);
  //Takes in a vector and returns a string
  vector<string> bookToString(const vector<Book*>&, bool includeTabs = false);
  //Takes a book and returns a string of its details
  string printBook(const Book* const, unsigned int time, bool includeTabs = false);
  
  /* Account related functions */
  accountComparator accountSortSelector(string criteria);
  //Takes an account and returns a string containing the details of the account
  //NOTE: It does not return the book details associated with the account
  string printAccount(const Account* const);
  //Takes in a vector of accounts and returns a string of the account details.
  //NOTE: Does NOT include the book details
  vector<string> accountToString(const vector<Account*>&);
  
  /*comparison functions*/
  static bool sortByTitle(Book*& lhs, Book*& rhs){return lhs->getTitle() < rhs->getTitle();}
  static bool sortByAuthor(Book*& lhs, Book*& rhs) {return lhs->getAuthor() < rhs->getAuthor();}
  static bool sortByGenre(Book*& lhs, Book*& rhs) {return lhs->getGenre() < rhs->getGenre();}
  static bool sortByBookID(Book*& lhs, Book*& rhs) {return lhs->getID() < rhs->getID();}
  static bool sortByPopularity( Book*& lhs, Book*& rhs) {return lhs->popularityScore() < rhs->popularityScore(); }
  static bool sortByName( Account*& lhs, Account*& rhs) { return lhs->getName() < rhs->getName(); }
  
  static bool sortByAccountID( Account*& lhs, Account*& rhs){ return lhs->getID() < rhs->getID(); }
  static bool sortByCheckouts(Account*& lhs, Account*& rhs) { return lhs->getBorrowSize()< rhs->getBorrowSize(); }
private:
  string tabEvaluator(bool include){return (include)? "\n\t":"\n"; }
};

#endif /* Archivist_hpp */
