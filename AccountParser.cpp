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
    return dataBase;
  }
  //Read the number of accounts in the file
  string numberOfAccounts;
  getline(file, numberOfAccounts);
  //Next iterate over the file
  for(unsigned int i = 0; i < stoi(numberOfAccounts); ++i){
    //Get the account
    string accountDetails;
    getline(file, accountDetails);
    //AccountDetails now contain the userID|name|numberofBooks
    //We will now read the rest of the lines based on the numberOfBooks the user
    //has checked out. Since it's guranteed to be the the last item of the string, we can use it without any validation
    unsigned int numBorrowed = atoi(&accountDetails[accountDetails.length()-1]);
    vector<string> borrowData(numBorrowed);
    //Read the lines from the file
    for(unsigned int i = 0; i < numBorrowed; ++i){
      string bookData;
      getline(file, bookData);
      borrowData.push_back(bookData);
    }
    //we have successfully parsed the bookData
    //So, we create the account
    //We add the account to the Pack object
    dataBase->addAccount(accountant(accountDetails));
    //Next, we map the accountID to the borrowData;
    initData[atoi(&accountDetails[0])] = borrowData;
  }
  file.close();
  return dataBase;
}

Account* AccountParser::accountant(const string& info){
  //Use the tokenize function to split the inputs
  vector<string> accountant = tokenizer(info);
  //We don't care about the number of books
  return new Account(stoi(accountant[0]), accountant[1]);
}
