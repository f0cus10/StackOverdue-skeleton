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
  //If a book with the given title and 
  bool bookExists();
  //If a book does not exist in the collection, add it to the collection. Else, return false
  bool addBook(Book* newBook);
  //Remove a book from the collection
  bool removeBook(unsigned int id);
  //Return a vector containing all the books in the library
  //NOTE: To be used with the exporter
  vector<const Book*> output();
  //Given the bookID, return the book
  const Book* getBook(unsigned int id);
  //If books are present containing the same substring, return a vector containg the boooks. Return empty vector, otherwise.
  //type must be either T or A;
  vector<const Book*> search(string phrase, char type);
  //Return a specified book to the library. Modifies borrowerID to the user who had the book. Modifies 
  void returnBook(unsigned int id, unsigned int& borrowerID, unsigned int& returnTime);
  
private:
  unordered_map<unsigned int, Book*> collection;
  unordered_map<unsigned int, Book*> graveyard;
};
#endif
