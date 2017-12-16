#include "Account.hpp"
//Overloaded Constructor
Account::Account(unsigned int id, string name){
  userID = id;
  username = name;
  //Micro optimisation for O(1) pushes
  borrowedBooksID.reserve(10);
  previousBorrows.reserve(10);
}
//Returns the ids of currently borrowedBooks
vector<unsigned int> Account::currentBorrowList() const{
  return borrowedBooksID;
}
//Returns the ids of previously borrowedBooks
vector<unsigned int> Account::previousBorrowList() const{
  return previousBorrows;
}
//Add a book to the list of currently borrowed books
void Account::checkout(unsigned int bookID, string bookAuthor, string genre){
  borrowedBooksID.push_back(bookID);
  favouriteAuthor[bookAuthor] += 1;
  favouriteGenre[genre] += 1;
}
//Return a book to the library and add it to the list of previous borrows
//TODO: Consider using UniqueVector instead of std::Vector
void Account::returnBook(unsigned int bookID){
  //Add the book into the list of previousBorrow
  unsigned int index;
  contains(bookID, index);
  previousBorrows.push_back(previousBorrows[index]);
  //Find the index of the bookID
  borrowedBooksID.erase(borrowedBooksID.begin()+index);
}

//If the bookID is being currently borrowed, return true and modify index
bool Account::contains(unsigned int bookID, unsigned int& index, char period){
  vector<unsigned int>* vecPointer;
  if(period == 'C'){
    vecPointer = &borrowedBooksID;
  }
  else{
    vecPointer = &previousBorrows;
  }
  for(unsigned int i = 0; i < vecPointer->size(); ++i){
    if(vecPointer->at(i) == bookID){
      index = i;
      return true;
    }
  }
  return false;
}
/*Recommendation getter */
string Account::getFavouriteGenre() const {
  return recommendSearch(favouriteGenre);
}
string Account::getSecondFavGenre() const {
  string ignore = recommendSearch(favouriteGenre);
  return recommendSearch(favouriteGenre, ignore);
}
string Account::getFavouriteAuthor() const{
  return recommendSearch(favouriteAuthor);
}
//Finds the most frequent item in the ordered list, does not take into account ignore
string Account::recommendSearch(const unordered_map<string, unsigned int>& hash, string ignore) const{
  string result = "";
  unsigned int resultFreq = 0;
  for(auto iter: hash){
    if(resultFreq < iter.second && iter.first != ignore){
      result = iter.first;
      resultFreq = iter.second;
    }
  }
  return result;
}
