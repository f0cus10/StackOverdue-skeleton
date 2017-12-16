//
//  Exporter.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/15/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#include "Exporter.hpp"
//Overloaded constructor
Exporter::Exporter(string book, string account){
  bookFileName = book;
  accountFileName = account;
}
//Takes in a shelf object and pack object as pointers and writes their data to bookFileName and accountFileName respectively
void Exporter::write(Shelf*& shelf, Pack*& data){
  bookExporter(shelf);
  accountExporter(shelf, data);
}
//Does book specific exporting
void Exporter::bookExporter(Shelf*& myShelf){
  ofstream myFile;
  myFile.open(bookFileName);
  myFile << myShelf->collectionSize();
  vector<Book*> data = myShelf->output();
  for(unsigned int i = 0; i < data.size(); ++i){
    myFile << data[i]->getID() << "|" << data[i]->getTitle() << "|";
    myFile << data[i]->getAuthor() << "|" << data[i]->getGenre() << "|" << data[i]->popularityScore() << "\n";
  }
  myFile.close();
}
void Exporter::accountExporter(Shelf*& myShelf, Pack*& data){
  ofstream myFile;
  myFile.open(accountFileName);
  myFile << data->getCollectionSize();
  vector<Account*> dataBase = data->getAccounts();
  for(unsigned int i = 0; i < dataBase.size(); ++i){
    if(dataBase[i] != nullptr){
      myFile << dataBase[i]->getID() << "|" << dataBase[i]->getName() << "|";
      
      vector<unsigned int> userBorrow = dataBase[i]->currentBorrowList();
      
      myFile<< userBorrow.size() << "\n";
      
      for(unsigned int j = 0; j < userBorrow.size(); ++j){
        if(myShelf->getBook(userBorrow[i]) != nullptr){
          myFile << myShelf->getBook(userBorrow[i])->getID() << "|";
          myFile << myShelf->getBook(userBorrow[i])->dueDate() << "|";
          myFile << myShelf->getBook(userBorrow[i])->getRenewed() << "\n";
        }
      }
    }
  }
  myFile.close();
}
