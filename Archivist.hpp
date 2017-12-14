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
  typedef bool(*bookComparator)(Book&, Book&);
  typedef bool(*accountComparator)(Account&, Account&);
  /* Book-related function */
  bookComparator bookSortSelector(string criteria);
  //Takes in a vector and returns a string
  string bookToString(vector<const Book* const>&);
  //Takes a book and returns a string of its details
  string printBook(const Book* const);
  
  /* Account related functions */
  accountComparator accountSortSelector(string criteria);
  //Takes an account and returns a string containing the details of the account
  //NOTE: It does not return the book details associated with the account
  string printAccount(const Account* const);
  //Takes in a vector of accounts and returns a string of the account details.
  //NOTE: Does NOT include the book details
  string accountToString(vector<const Account* const>&);
};

#endif /* Archivist_hpp */
