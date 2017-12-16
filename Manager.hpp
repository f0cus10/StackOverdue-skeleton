#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <unordered_map>
#include <string>
#include "Shelf.hpp"
#include "Pack.hpp"
#include "Archivist.hpp"
#include "Time.hpp"
using namespace std;
//This class is too big.
class Manager{
public:
  //If a book with the same title and author exists, return true
  bool bookExists(string title, string author){return shelf->bookExists(title, author); }
  //Returns true if the account can borrow, modifies the string to the reason for not being able to borrow.
  bool canBorrow(unsigned int, string&);
  //Returns true if a book or user with the specified id exists
  //the char determines the type to search for
  bool isValid(unsigned int, char);
  //If account has overdue books, return true and modify number to the number of overdue books.
  bool hasOverdue(unsigned int accountID, unsigned int& number);
  //Overloaded Constructor
  Manager(string bookFile = "", string accountFileName = "");
  //Overloaded Destructor
  ~Manager();
  //Given the correct criteria, the function will return a string consisting of all the the books in the library.
  //If there are no books, return "No books in your library"
  vector<string> browse(string criteria);
  //Returns a full description of the specified book. If it is checked out, print those details as well.
  string book(unsigned int bookID, bool tabs);
  //Prints short description for all books in the library containing a specified phrase in either the book's title or author.
  //Case-sensitive. Returns "No search results found", if none found.
  vector<string> search(string phrase, string criteria);
  //Returns a description of the accounts
  vector<string> accounts(string criteria, unordered_map<unsigned int, vector<string> >&);
  //Returns a full description of a specified account
  string account(unsigned int accountID);
  //Checks out a specific book to a specified account
  bool checkout(unsigned int bookID, unsigned int accountID, unsigned int dueDate = 0);
  //Renews all the books in a specified account
  string renew(unsigned int accountID, unsigned int newDueDate = 0);
  //Returns a specific book to the library. Indicate if it was returned on time or overdue by some period of time.
  string returnBook(unsigned int bookID);
  //Generates a list of five book recommendations for a specified account
  vector<string> recommend(unsigned int accountID, vector<string>&);
  //Adds a book with the title, author and genre to the collection
  //Does not check whether the book already exists
  string addBook(string title, string author, string genre);
  string removeBook(unsigned int bookID);
  string addAccount(string name);
  string removeAccount(unsigned int accountID);
  string system();
  string time(unsigned int passTime);
  void exportData(string bookName, string accountName);  
  vector<unsigned int> getNonExistent()const {return nonexistent;}
private:
  /* Database */
  Shelf* shelf;
  Pack* users;
  
  /* Initial step members */
  unordered_map<unsigned int, vector<string> > initialState;
  vector<unsigned int> nonexistent;
  //Uses initialState to update the borrow status from the user files
  //After completion, erase the map
  void updateInitialState();
  
  /* Assistant Members to provide useful algorithms and functions*/
  Archivist archivist;
  Time systemTime;
};
#endif
