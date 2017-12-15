//
//  AccountParser.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/8/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#include "AccountParser.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Account.hpp"
#include "Pack.hpp"
using namespace std;
Pack* AccountParser::buildPack(unordered_map<unsigned int, vector<string> >& initData){
  //First, create a file object and read the initial data
  ifstream file;
  file.open(fileName);
  //Dynamically allocate a Pack object and do a file check
  Pack* dataBase = new Pack();
  if(!file.good()){
    cout << "Could not find file \"" + fileName + "\". Skipping." << endl;
    return dataBase;
  }
  //Else, start parsing the data line
  cout << "Loading accounts from \"" + fileName + "\"." << endl;
  //Read the number of accounts in the file
  string numberOfAccounts;
  getline(file, numberOfAccounts);
  //Next iterate over the file
  for(unsigned int i = 0; i < stoi(numberOfAccounts); ++i){
    //Get the account
    string line;
    getline(file, line);
    vector<string> accountDetails = tokenizer(line);
    unsigned int numBorrowed = stoi(accountDetails[2]);
    vector<string> borrowData;
    borrowData.reserve(numBorrowed);
    //Read the lines from the file
    for(unsigned int i = 0; i < numBorrowed; ++i){
      string bookData;
      getline(file, bookData);
      if(bookData!= "") borrowData.push_back(bookData);
    }
    //we have successfully parsed the bookData
    //So, we create the account
    //We add the account to the Pack object
    dataBase->addAccount(accountant(accountDetails));
    //Next, we map the accountID to the borrowData;
    initData[stoi(accountDetails[0])] = borrowData;
  }
  file.close();
  return dataBase;
}

Account* AccountParser::accountant(const vector<string>& info){
  //We don't care about the number of books
  return new Account(stoi(info[0]), info[1]);
}
