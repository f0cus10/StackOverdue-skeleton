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
#include "Parser.hpp"
#include "BookParser.hpp"
#include "AccountParser.hpp"
#include "Archivist.hpp"
#include "Exporter.hpp"
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
//Returns true if the account can borrow, modifies the string to the reason for not being able to borrow.
bool Manager::canBorrow(unsigned int id, string& reason){
  unsigned int decoy = 0;
  if(users->getAccount(id)->borrowSize() >= 10){
    reason = "Account already has 10 books checked out.";
    return false;
  }
  else if(hasOverdue(id,decoy)){
    reason = "Account has books overdue.";
    return false;
  }
  return true;
}
//Returns true if a book or user with the specified id exists
//the char determines the type to search for
bool Manager::isValid(unsigned int id, char type){
  switch (type) {
    case 'B':
      if(shelf->getBook(id) == nullptr) return false;
      return true;
    case 'A':
      if(users->getAccount(id) == nullptr) return false;
      return true;
    default:
      return true;
  }
}
//If account has overdue books, return true and modify number to the number of overdue books.
bool Manager::hasOverdue(unsigned int accountID, unsigned int& number){
  vector<unsigned int> borrowed = users->getAccount(accountID)->currentBorrowList();
  for(auto iter: borrowed){
    if(shelf->getBook(iter)->isOverdue(systemTime.getTime())){
      number += 1;
    }
  }
  if(number > 0) return true;
  return false;
}
//Given the correct criteria, the function will return a string consisting of all the the books in the library.
//If there are no books, return "No books in your library"
vector<string> Manager::browse(string criteria){
  //We must decide which comparison function to use based on the criteria
  //Use else-if with function pointers
  //Import the entire shelf as a vector
  vector<Book*> sortCandidate = shelf->output();
  
  bool(*comparator)(Book*&, Book*&) = archivist.bookSortSelector(criteria);
  //Then, we pass in the vector in the sorting algorithm
  sort(sortCandidate.begin(), sortCandidate.end(), comparator);
  return archivist.bookToString(sortCandidate);
}
//Returns a full description of the specified book. If it is checked out, print those details as well.
//If book does not exist, return ""
string Manager::book(unsigned int bookID, bool tabs){
  Book* const tmp = shelf->getBook(bookID);
  if (tmp == nullptr){
    return "BookID# " + to_string(bookID) + " not found.\n";
  }
  return archivist.printBook(tmp, systemTime.getTime(), tabs);
}
//Returns a description of the accounts
vector<string> Manager::accounts(string criteria, unordered_map<unsigned int, vector<string> >& bookMapper){
  vector< Account*> sortCandidate = users->getAccounts();
  bool (*comparator)(Account*&, Account*&) = archivist.accountSortSelector(criteria);
  sort(sortCandidate.begin(), sortCandidate.end(), comparator);
  //Create the user account list
  vector<string> accountList = archivist.accountToString(sortCandidate);
  for(unsigned int i = 0; i < sortCandidate.size(); ++i){
    //First convert currentBorrowList into books
    //create a temp vector
    vector<Book*> tmp;
    tmp.reserve(sortCandidate[i]->borrowSize());
    for(unsigned int j = 0; j < sortCandidate[i]->borrowSize(); ++j){
      tmp.push_back(shelf->getBook(sortCandidate[i]->currentBorrowList()[j]));
    }
    //Temp should contain all book pointers for that user
    bookMapper[i] = archivist.bookToString(tmp, true);
  }
  return accountList;
}
//Returns a full description of a specified account
string Manager::account(unsigned int accountID){
  string result = archivist.printAccount(users->getAccount(accountID));
  result += "\n";
  vector<unsigned int> tmp = users->getAccount(accountID)->currentBorrowList();
  for(unsigned int i = 0; i < tmp.size(); ++i){
    result += "\t" + to_string(i+1) + ".\n";
    result += "\t" +archivist.printBook(shelf->getBook(tmp[i]), systemTime.getTime(), true);
    result += "\n";
  }
  return result;
}
//Checks out a specific book to a a specified account
//Input must be evaluated beforehand
bool Manager::checkout(unsigned int bookID, unsigned int accountID, unsigned int dueDate){
  unsigned int bookIndex;
  if (dueDate == 0) dueDate = systemTime.getTime()+15;
  //If book was borrowed previously, do not raise the popularity
  bool status;
  if(users->getAccount(accountID)->contains(bookID, bookIndex, 'P')){
    status = shelf->getBook(bookID)->checkout(accountID, dueDate, false);
  }
  status = shelf->getBook(bookID)->checkout(accountID, dueDate, true);
  if(status){
    users->getAccount(accountID)->checkout(bookID, shelf->getBook(bookID)->getAuthor(), shelf->getBook(bookID)->getGenre());
  }
  return status;
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
    result += archivist.printBook(shelf->getBook(borrowList[i]), true);
    
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
  if(tmp->availability() == 'A'){
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
//string Manager::recommend(unsigned int accountID);
string Manager::addBook(string title, string author, string genre){
  //To save time, we'll do something radical
  unsigned int newID = shelf->generateID();
  shelf->addBook(new Book(newID, title, author, genre));
  return "BookID# " + to_string(newID) + " sucessfully created.\n";
}
string Manager::removeBook(unsigned int bookID){
  string outcome = "";
  if(shelf->getBook(bookID)->availability() == 'B'){
    outcome += "Force returning the book from AccountID# " + to_string(shelf->getBook(bookID)->borrower()) + ".\n";
    returnBook(bookID);
  }
  outcome += "\"" + shelf->getBook(bookID)->getTitle() + "\" by ";
  outcome += shelf->getBook(bookID)->getAuthor() + " successfully removed.\n";
  shelf->removeBook(bookID);
  return outcome;
}
string Manager::addAccount(string name){
  unsigned int newID = users->generateID();
  users->addAccount(new Account(newID, name));
  return "AccountID# " + to_string(newID) + " successfully created.\n";
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
string Manager::time(unsigned int passTime){
  unsigned int oldTime = systemTime.getTime();
  systemTime.updateTime(passTime);
  unsigned int newTime = systemTime.getTime();
  string result = "Travelled through " + to_string(passTime) + " days through time. (";
  result += to_string(oldTime) + " --> " + to_string(newTime) + ").\n";
  return result;
}
//Uses initialState to update the borrow status from the user files
//After completion, erase the map
void Manager::updateInitialState(){
  //Iterate over each userID and update info
  for(auto iter: initialState){
    //Take each of the elements in the mapped vector and tokenize it
    for(auto eachElement: iter.second){
      vector<string> updateInformation = Parser::tokenizer(eachElement);
      //Checkout the book to the user
      if(shelf->getBook(stoi(updateInformation[0])) == nullptr){
        nonexistent.push_back(stoi(updateInformation[0]));
      }
      else{
        checkout(stoi(updateInformation[0]), iter.first);
      }
      //Renew the book number of times listed
      for(unsigned int i = 0; i < stoi(updateInformation[2]); ++i){
        renew(iter.first, stoi(updateInformation[1]));
      }
    }
  }
  initialState.clear();
}
string Manager::system(){
  string result = "";
  result += "System time: " + to_string(systemTime.getTime()) + ".\n";
  result += "Number of books: " + to_string(shelf->collectionSize()) + ".\n";
  //To count the number of overdue books, we'll use a simple principal but a slow one
  vector<Account*> data = users->getAccounts();
  unsigned int numberOfOverdue = 0;
  unsigned int numberOfOverdueAccounts = 0;
  for(unsigned int i = 0; i < data.size(); ++i){
    unsigned int tmp = 0;
    if(hasOverdue(data[i]->getID(), tmp)){
      numberOfOverdueAccounts += 1;
      numberOfOverdue += tmp;
    }
  }
  result += "Number of overdue books: " + to_string(numberOfOverdue) + ".\n";
  result += "Number of accounts: " + to_string(data.size()) + ".\n";
  result += "Number of overdue accounts: " + to_string(numberOfOverdueAccounts) + ".\n";
  return result;
}
//Prints short description for all books in the library containing a specified phrase in either the book's title or author.
//Case-sensitive. Returns "No search results found", if none found.
vector<string> Manager::search(string phrase, string criteria){
  char type = '\0';
  if(criteria == "title"){
    type = 'T';
  }
  else if(criteria == "author"){
    type = 'A';
  }
  vector<Book*> searchResult = shelf->search(phrase, type);
  return archivist.bookToString(searchResult);
}
//Generates a list of five book recommendations for a specified account
vector<string> Manager::recommend(unsigned int accountID, vector<string>& choices){
  choices.push_back(users->getAccount(accountID)->getFavouriteGenre());
  choices.push_back(users->getAccount(accountID)->getSecondFavGenre());
  choices.push_back(users->getAccount(accountID)->getFavouriteAuthor());
  /* Gather all the results */
  vector<Book*> favGenre;
  vector<Book*> secGenre;
  vector<Book*> favAuthor;
  if(choices[0] != "") favGenre = shelf->search(choices[0], 'G');
  if(choices[1] != "") secGenre = shelf->search(choices[1], 'G');
  if(choices[2] != "") favAuthor = shelf->search(choices[2], 'A');
  /* Sort these all */
  vector<Book*> tmp;
  sort(favGenre.begin(), favGenre.end(), archivist.sortByPopularity);
  sort(secGenre.begin(), secGenre.end(), archivist.sortByPopularity);
  sort(favAuthor.begin(), favAuthor.end(), archivist.sortByPopularity);
  //Retrieve the last 2 elements from favGenre
  if(!(favGenre.size() < 2)){
    tmp.push_back(favGenre[favGenre.size()-1]);
    tmp.push_back(favGenre[favGenre.size()-2]);
  }
  else{
    tmp.push_back(nullptr);
    tmp.push_back(nullptr);
  }
  if(!(secGenre.size() < 2)){
    tmp.push_back(secGenre[secGenre.size()-1]);
    tmp.push_back(secGenre[secGenre.size()-2]);
  }
  else{
    tmp.push_back(nullptr);
    tmp.push_back(nullptr);
  }
  if(!(favAuthor.size() < 2)){
    tmp.push_back(favAuthor[favAuthor.size()-1]);
  }
  else{
    tmp.push_back(nullptr);
  }
  return archivist.bookToString(tmp);
}
void Manager::exportData(string bookName, string accountName){
  Exporter* exp = new Exporter(bookName, accountName);
  //For some stupid reason shelf and users can't be passed as const *.
  //This is stupid, Object * should be able to bind as const object* but not vice-versa. smh.
  exp->write(shelf, users);
  delete exp;
}
