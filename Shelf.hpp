#ifndef SHELF_HPP
#define SHELF_HPP
#include "Book.hpp"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Shelf{
public:
  //Default constructor
  //Overloaded Destructor
  ~Shelf();
  //Return the size of the collection
  unsigned int collectionSize(){ return collection.size();}
  //If a book with the given title and author exists, return true;
  bool bookExists(string title, string author);
  //If a book does not exist in the collection, add it to the collection. Else, return false
  bool addBook(Book* newBook);
  //Remove a book from the collection
  bool removeBook(unsigned int id);
  //Return a vector containing all the books in the library
  //NOTE: To be used with the exporter
  vector<Book*> output();
  //Given the bookID, return the book
  Book* getBook(unsigned int id);
  //If books are present containing the same substring, return a vector containg the boooks. Return empty vector, otherwise.
  //type must be either T or A;
  vector<Book*> search(string phrase, char type);
  //Return a specified book to the library. Modifies borrowerID to the user who had the book. Modifies 
  void returnBook(unsigned int id, unsigned int& borrowerID, unsigned int& returnTime);
  unsigned int generateID() const {return maxID; }
private:
  unordered_map<unsigned int, Book*> collection;
  unordered_map<unsigned int, Book*> graveyard;
  unsigned int maxID = 0;
};
#endif
