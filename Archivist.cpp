//
//  Archivist.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/14/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#include "Archivist.hpp"
#include "Book.hpp"
#include "Account.hpp"
#include <string>
using namespace std;
//Probably made this way too complicated
typedef bool(*bookComparator)(Book*&, Book*&);
typedef bool(*accountComparator)(Account*&, Account*&);
/* Book-related function */
bookComparator Archivist::bookSortSelector(string criteria){
  if(criteria == "title"){
    return &sortByTitle;
  }
  else if(criteria == "author"){
    return &sortByAuthor;
  }
  else if(criteria == "genre"){
    return &sortByGenre;
  }
  else if(criteria == "bookid"){
    return &sortByBookID;
  }
  else{
    return &sortByPopularity;
  }
}
//Takes in a vector and returns a string
vector<string> Archivist::bookToString(const vector<Book*>& entries, bool includeTabs){
  vector<string> result;
  for(unsigned int i = 0; i < entries.size(); ++i){
    string line = "";
    line += "\"" + entries[i]->getTitle() + "\" by " + entries[i]->getAuthor() + " (BookID# " + to_string(entries[i]->getID()) + ") [" + entries[i]->getGenre() + "].";
    if(!includeTabs) line += (entries[i]->availability() == 'B')? " CHECKED OUT (AccountID#" + to_string(entries[i]->borrower()) + ")." : " AVAILABLE.";
    line += tabEvaluator(includeTabs);
    result.push_back(line);
  }
  return result;
}
//Takes a book and returns a string of its details
//string Archivist::printBook(const Book* const bookInfo)
/* Account related functions */
accountComparator Archivist::accountSortSelector(string criteria){
  if(criteria == "name"){
    return &sortByName;
  }
  else if(criteria == "accountid"){
    return &sortByAccountID;
  }
  return &sortByCheckouts;
}
//Takes an account and returns a string containing the details of the account
//NOTE: It does not return the book details associated with the account
//string Archivist::printAccount(const Account* const);
//Takes in a vector of accounts and returns a string of the account details.
vector<string> Archivist::accountToString(const vector<Account*>& database){
  vector<string> result;
  for(unsigned int i = 0; i < database.size(); ++i){
    string line = "";
    line += database[i]->getName() + " (AccountID# " + to_string(database[i]->getID()) + "). ";
    unsigned int size = database[i]->currentBorrowList().size();
    line += (size==0)? " No " : to_string(size);
    line += " books checked out. \n";
    result.push_back(line);
  }
  return result;
}
//Takes a book and returns a string of its details
string Archivist::printBook(const Book* const book, unsigned int time, bool includeTabs){
  string ending = tabEvaluator(includeTabs);
  string result = "";
  result += "Name: \"" + book->getTitle() + "\"" + ending;
  result += "Author: " + book->getAuthor() + ending;
  result += "BookID# " + to_string(book->getID()) + ending;
  result += "Popularity Score: " + to_string(book->popularityScore()) + ending;
  if(!includeTabs && book->availability() == 'B') result += "Borrower AccountID# " + to_string(book->borrower()) + ending;
  result += "Due Date: " + to_string(book->dueDate()) + ending;
  result += "Times Renewed: " + to_string(book->getRenewed()) + ending;
  if(book->isOverdue(time)){
    result += "OVERDUE" + ending;
  }
  else if(!includeTabs && book->availability() == 'A'){
    result += "AVAILABLE" + ending;
  }
  return result;
}
string Archivist::printAccount(const Account* const user){
  string result = "";
  result += "Name: " + user->getName() + "\n";
  result += "AccountID#: " + to_string(user->getID()) + "\n";
  result += to_string(user->currentBorrowList().size()) + " books checked out";
  return result;
}
