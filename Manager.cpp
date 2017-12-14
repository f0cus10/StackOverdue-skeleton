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
#include "Shelf.hpp"
#include "Pack.hpp"

using namespace std;

//Given the correct criteria, the function will return a string consisting of all the the books in the library.
//If there are no books, return "No books in your library"
string Manager::browse(string criteria){
  
}
//Returns a full description of the specified book. If it is checked out, print those details as well.
string Manager::book(unsigned int bookID);
//Prints short description for all books in the library containing a specified phrase in either the book's title or author.
//Case-sensitive. Returns "No search results found", if none found.
string Manager::search(string criteria);
//Returns a description of the accounts
string Manager::accounts(string criteria);
//Returns a full description of a specified account
string Manager::account(unsigned int accountID);
//Checks out a specific book to a a specified account
bool Manager::checkout(unsigned int bookID, unsigned int accountID);
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
