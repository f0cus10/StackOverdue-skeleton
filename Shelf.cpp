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

//Add newBook to the collection. Book must not exist beforehand
bool Shelf::addBook(Book* newBook){
  //Check if the same id number exists
  auto search = collection.find(newBook->getID());
  if(search!= collection.end()){
    return false;
  }
  collection[newBook->getID()] = newBook;
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
Book* const Shelf::getBook(unsigned int id){
  return collection[id];
}
//Return a vector containing all the books in the library
//NOTE: To be used with the exporter
vector<const Book* const> Shelf::output(){
  vector<const Book* const> tmp;
  for(auto iter = collection.begin(); iter != collection.end(); ++iter){
    tmp.push_back(iter->second);
  }
  return tmp;
}
//If books are present containing the same substring, return a vector containg the boooks. Return empty vector, otherwise.
//type must be either T or A;
//TODO: Finish this
vector<const Book* const> Shelf::search(string phrase, char type){
  vector<const Book* const> temp;
  return temp;
}
//Return a specified book to the library. Modifies borrowerID to the user who had the book. Modifies
void Shelf::returnBook(unsigned int id, unsigned int& borrowerID, unsigned int& returnTime){
  borrowerID = collection[id]->borrower();
  returnTime = collection[id]->dueDate();
  collection[id]->returnBook();
  return;
}
