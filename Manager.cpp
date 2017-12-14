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

using namespace std;

//Given the correct criteria, the function will return a string consisting of all the the books in the library.
//If there are no books, return "No books in your library"
string Manager::browse(string criteria){
  //We must decide which comparison function to use based on the criteria
  //Use else-if with function pointers
  //Import the entire shelf as a vector
  vector<const Book*> sortCandidate = shelf->output();
  //Then, we pass in the vector in the sorting algorithm
  sort(sortCandidate.begin(), sortCandidate.end());
  return vectorToString(sortCandidate);
}
//Returns a full description of the specified book. If it is checked out, print those details as well.
//If book does not exist, return ""
string Manager::book(unsigned int bookID){
  //PLACEHOLDER
  return shelf->getBook(bookID)->getAuthor();
}
//Prints short description for all books in the library containing a specified phrase in either the book's title or author.
//Case-sensitive. Returns "No search results found", if none found.
string Manager::search(string criteria){
  return "PLACEHOLDER";
}
//Returns a description of the accounts
string Manager::accounts(string criteria){
  return "PLACEHOLDER";
}
//Returns a full description of a specified account
string Manager::account(unsigned int accountID){
  return "PLACEHOLDER";
}
//Checks out a specific book to a a specified account
bool Manager::checkout(unsigned int bookID, unsigned int accountID){
  //First, checkout the book
}
//Renews all the books in a specified account
string Manager::renew(unsigned int accountID);
//Returns a specific book to the library. Indicate if it was returned on time or overdue by some period of time.
string Manager::returnBook(unsigned int bookID);
//Generates a list of five book recommendations for a specified account
string Manager::recommend(unsigned int accountID);
string Manager::addBook(string title, string author, string genre);
string Manager::removeBook(unsigned int bookID);
string Manager::addAccount(string name);
string Manager::removeAccount(unsigned int accountID);
string Manager::system();
string Managertime(unsigned int passTime);
string Manager::exportData();
string Manager::help();

