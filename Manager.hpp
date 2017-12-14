#include <unordered_map>
#include <string>
#include "Shelf.hpp"
#include "Pack.hpp"
#include "Archivist.hpp"
#include "Time.hpp"
using namespace std;
class Manager{
public:
  //Overloaded Constructor
  Manager(string bookFile = "", string accountFileName = "");
  //Overloaded Destructor
  ~Manager();
  //Given the correct criteria, the function will return a string consisting of all the the books in the library.
  //If there are no books, return "No books in your library"
  string browse(string criteria);
  //Returns a full description of the specified book. If it is checked out, print those details as well.
  string book(unsigned int bookID);
  //Prints short description for all books in the library containing a specified phrase in either the book's title or author.
  //Case-sensitive. Returns "No search results found", if none found.
  string search(string phrase, char criteria);
  //Returns a description of the accounts
  string accounts(string criteria);
  //Returns a full description of a specified account
  string account(unsigned int accountID);
  //Checks out a specific book to a a specified account
  bool checkout(unsigned int bookID, unsigned int accountID);
  //Renews all the books in a specified account
  string renew(unsigned int accountID, unsigned int newDueDate = 0);
  //Returns a specific book to the library. Indicate if it was returned on time or overdue by some period of time.
  string returnBook(unsigned int bookID);
  //Generates a list of five book recommendations for a specified account
  string recommend(unsigned int accountID);
  //Adds a book with the title, author and genre to the collection
  //Does not check whether the book already exists
  string addBook(string title, string author, string genre);
  string removeBook(unsigned int bookID);
  string addAccount(string name);
  string removeAccount(unsigned int accountID);
  string system();
  string time(unsigned int passTime);
  string exportData();
  string help();
private:
  /* Database */
  Shelf* shelf;
  Pack* users;
  
  /* Initial step members */
  unordered_map<unsigned int, vector<string> > initialState;
  //Uses initialState to update the borrow status from the user files
  //After completion, erase the map
  void updateInitialState();
  
  /* Assistant Members to provide useful algorithms and functions*/
  Archivist archivist;
  Time systemTime;
};
