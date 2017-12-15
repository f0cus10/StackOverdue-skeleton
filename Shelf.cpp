//Implementation file for Shelf.hpp
#include "Shelf.hpp"
//Overloaded Destructor
Shelf::~Shelf(){
  //First call delete on all the books in collection
  for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
    delete iter->second;
  }
  //Then, do the same thing to books in the graveyard library
  for(auto iter = graveyard.begin(); iter != graveyard.end(); ++iter){
    delete iter->second;
  }
  //Erase all the pointers
  collection.clear();
  graveyard.clear();
}
//If a book with the given title and author exists, return true;
//O(n) search
bool Shelf::bookExists(string title, string author){
  for(auto iter = collection.begin(); iter != collection.end(); ++iter){
    if(iter->second->getTitle() == title && iter->second->getAuthor() == author){
      return true;
    }
  }
  return false;
}
//Add newBook to the collection. Book must not exist beforehand
bool Shelf::addBook(Book* newBook){
  //Check if the same id number exists
  collection[newBook->getID()] = newBook;
  if(maxID < newBook->getID()){
    maxID = newBook->getID() + 1;
  }
  return true;
}
//Remove a book from the collection
bool Shelf::removeBook(unsigned int id){
  //Add the book to graveyard
  auto candidate = collection.find(id);
  if(candidate != collection.end()){
    graveyard[id] = collection[id];
    collection.erase(candidate);
    return true;
  }
  return false;
}
//Return a vector containing all the books in the library
Book* Shelf::getBook(unsigned int id){
  return collection[id];
}
//Return a vector containing all the books in the library
//NOTE: To be used with the exporter

vector<Book*> Shelf::output(){
  vector<Book*> tmp;
  tmp.reserve(collection.size());
  for (auto value: collection){
    if(value.second!= nullptr)tmp.push_back(value.second);
  }
  return tmp;
}
//If books are present containing the same substring, return a vector containg the boooks. Return empty vector, otherwise.
//type must be either T or A;
//TODO: Finish this
vector<Book*> Shelf::search(string phrase, char type){
  vector<Book*> temp;
  return temp;
}
//Return a specified book to the library. Modifies borrowerID to the user who had the book. Modifies
void Shelf::returnBook(unsigned int id, unsigned int& borrowerID, unsigned int& returnTime){
  borrowerID = collection[id]->borrower();
  returnTime = collection[id]->dueDate();
  collection[id]->returnBook();
  return;
}
