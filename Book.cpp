#include "Book.hpp"
#include <string>

Book::Book(unsigned int id, string title, string author, string gen, unsigned int score){
  bookID = id;
  bookTitle = title;
  bookAuthor = author;
  genre = gen;
  popScore = score;
}
//If book have been renewed twice, returns false. Otherwise, renews books and returns true
bool Book::renew(unsigned int currentTime){
  //Check if book has been renewed twice
  if(renewed >= 2){
    return false;
  }
  due = currentTime+15;
  renewed += 1;
  return true;
}
//Returns false if book has been already borrowed. Else, removes borrow information and returns true
void Book::returnBook(){
  borrowerID = 0;
  due = 0;
  renewed = 0;
  status = 'A';
}
//Checkout the book
//If available, checkout book and return true; else, false.
bool Book::checkout(unsigned int userID, unsigned int currentTime, bool raisePopularity){
  //If book is borrowed, return false;
  if(status == 'B'){
    return false;
  }
  borrowerID = userID;
  due = currentTime + 15;
  renewed = 0;
  status = 'B';
  if(raisePopularity){
    popScore += 1;
  }
  return true;
}
