//
//  Manager.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/13/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//
#include "Manager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Shelf.hpp"
#include "Pack.hpp"
#include "Book.hpp"
#include "BookParser.hpp"
#include "AccountParser.hpp"

using namespace std;
Manager::Manager(string bookFile, string accountFileName){
  BookParser bookReader(bookFile);
  AccountParser accountReader(accountFileName);
  //Import the pointers
  shelf = bookReader.buildShelf();
  users = accountReader.buildPack(initialState);
  //Update initial status
  updateInitialState();
}
Manager::~Manager(){
  delete shelf;
  delete users;
}
//Given the correct criteria, the function will return a string consisting of all the the books in the library.
//If there are no books, return "No books in your library"
string Manager::browse(string criteria){
  //We must decide which comparison function to use based on the criteria
  //Use else-if with function pointers
  //Import the entire shelf as a vector
  vector<const Book* const> sortCandidate = shelf->output();
  bool (*comparator)(Book&, Book&) = archivist.bookSortSelector(criteria);
  //Then, we pass in the vector in the sorting algorithm
  sort(sortCandidate.begin(), sortCandidate.end(), comparator);
  return archivist.bookToString(sortCandidate);
}
//Returns a full description of the specified book. If it is checked out, print those details as well.
//If book does not exist, return ""
string Manager::book(unsigned int bookID){
  Book* const tmp = shelf->getBook(bookID);
  return archivist.printBook(tmp);
}
//Prints short description for all books in the library containing a specified phrase in either the book's title or author.
//Case-sensitive. Returns "No search results found", if none found.
string Manager::search(string phrase, char criteria){
  vector<const Book* const> searchResult = shelf->search(phrase, criteria);
  return archivist.bookToString(searchResult);
}
//Returns a description of the accounts
string Manager::accounts(string criteria){
  vector<const Account* const> sortCandidate = users->getAccounts();
  bool(*comparator)(Account&, Account&) = archivist.accountSortSelector(criteria);
  sort(sortCandidate.begin(), sortCandidate.end(), comparator);
  //
  return archivist.accountToString(sortCandidate);
}
//Returns a full description of a specified account
string Manager::account(unsigned int accountID){
  return archivist.printAccount(users->getAccount(accountID));
}
//Checks out a specific book to a a specified account
//Input must be evaluated beforehand
bool Manager::checkout(unsigned int bookID, unsigned int accountID){
  unsigned int bookIndex;
  //If book was borrowed previously, do not raise the popularity
  if(users->getAccount(accountID)->contains(bookID, bookIndex, 'P')){
    return shelf->getBook(bookID)->checkout(accountID, systemTime.getTime(), false);
  }
  return shelf->getBook(bookID)->checkout(accountID, systemTime.getTime(), true);
}
//Renews all the books in a specified account
string Manager::renew(unsigned int accountID, unsigned int newDueDate){
  if(newDueDate == 0){
    newDueDate = systemTime.getTime();
  }
  //Try and renew tmp
  vector<unsigned int> borrowList = users->getAccount(accountID)->currentBorrowList();
  unsigned int totalBorrowed = borrowList.size();
  unsigned int sucessfullyRenewed = 0;
  string result = "";
  for(unsigned int i = 0; i < totalBorrowed; ++i){
    //Add the book description to the result
    result += "\t";
    result += to_string(i+1) + ".\n";
    //TODO: add a tabbed output parameter to the printBook() function
    result += archivist.printBook(shelf->getBook(borrowList[i]));
    
    if(shelf->getBook(borrowList[i])->renew(newDueDate)){
      result += "Book successfully renewd.\n";
    }
    else{
      result += "Book already renewed twice.\n";
    }
  }
 return to_string(sucessfullyRenewed) + " out of " + to_string(totalBorrowed) + " books successfully renewd.\n" + result;
}
//Returns a specific book to the library. Indicate if it was returned on time or overdue by some period of time.
string Manager::returnBook(unsigned int bookID){
  //First return the book from the shelf
  Book* const tmp = shelf->getBook(bookID);
  if(tmp->availability() == 'B'){
    return "Book is not currently checked out.";
  }
  unsigned int dueDate = tmp->dueDate();
  unsigned int userID = tmp->borrower();
  
  users->getAccount(userID)->returnBook(bookID);
  tmp->returnBook();
  string output = "Book successfully returned by AccountID# " + to_string(userID);
  if(dueDate < systemTime.getTime()){
    return output + " (overdue by " + to_string(dueDate-systemTime.getTime()) + " days).\n";
  }
  return output + " (on time).\n";
}
//Generates a list of five book recommendations for a specified account
//F*CK
string Manager::recommend(unsigned int accountID);
string Manager::addBook(string title, string author, string genre){
  //To save time, we'll do something radical
  shelf->addBook(new Book(shelf->generateID(), title, author, genre));
}
string Manager::removeBook(unsigned int bookID){
  string outcome = "";
  if(shelf->getBook(bookID)->availability() == 'B'){
    outcome += "Force returning the book from AccountID# " + to_string(shelf->getBook(bookID)->borrower()) + ".\n";
    returnBook(bookID);
  }
  outcome += "\"" + shelf->getBook(bookID)->getTitle() + "\" by ";
  outcome += shelf->getBook(bookID)->getAuthor() + " successfully removed.\n";
  return outcome;
}
string Manager::addAccount(string name){
  users->addAccount(new Account(users->generateID(), name));
}
string Manager::removeAccount(unsigned int accountID){
  string outcome = "";
  vector<unsigned int> borrowList = users->getAccount(accountID)->currentBorrowList();
  //Iterate over them and return every book
  for(unsigned int i = 0; i < borrowList.size(); ++i){
    returnBook(borrowList[i]);
    outcome += "\"" + shelf->getBook(borrowList[i])->getTitle() + "\"";
    outcome += " by " + shelf->getBook(borrowList[i])->getAuthor();
    outcome += " (BookID# " + to_string(borrowList[i]) + ") force returned.\n";
  }
  outcome += users->getAccount(accountID)->getName() + "'s account successfully removed.\n";
  users->removeAccount(accountID);
  return outcome;
}
string Manager::system(){
  
}
string Managertime(unsigned int passTime);
string Manager::exportData();
string Manager::help();

