//
//  BookParser.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/7/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "BookParser.hpp"
#include "Book.hpp"
using namespace std;
Shelf* BookParser::buildShelf(){
  //First, allocate memory for shelf
  Shelf* temp = new Shelf();
  //Then open the file
  ifstream file;
  file.open(fileName);
  if(!file.good()){
    cout << "Could not find file " + fileName + ". Skipping.";
    return temp;
  }
  //Else, start parsing the data line
  cout << "Loading books from \"" + fileName + "\".";
  //Get the first line from the file
  vector<string> data;
  string numberOfLines;
  getline(file, numberOfLines);
  for(unsigned int i = 0; i < stoi(numberOfLines); ++i){
    string line;
    getline(file, line, '\n');
    data.push_back(line);
  }
  //Then, we build as many books as there are in the vector
  for (unsigned int i = 0; i < data.size(); ++i) {
    //Take each string, tokenize it and return a dynamically allocated book pointer
    temp->addBook(bookWriter(data[i]));
  }
  return temp;
}
//Uses info, which is one line of input from the files, to
Book* BookParser::bookWriter(const string& info){
  vector<string> builder = tokenizer(info);
  //Next, we use it to make a book object
  return new Book(stoi(builder[0]), builder[1], builder[2], builder[3], stoi(builder[4]));
}
