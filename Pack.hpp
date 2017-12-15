//
//  Pack.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/8/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef Pack_hpp
#define Pack_hpp

#include <iostream>
#include <unordered_map>
#include "Account.hpp"
using namespace std;

class Pack{
public:
  //Default Constructor
  //Overloaded Destructor
  ~Pack();
  //Given an account, add it to the collection
  void addAccount(Account* newAccount);
  //Given a userID, add it to the graveyard
  void removeAccount(unsigned int accountID);
  //Return a vector containing all the accounts for the sorting algorithms
  vector<Account*> getAccounts() const;
  //Return a const-pointer to the account, given accountID
  Account* const getAccount(unsigned int accountID);
  //Generate a new userID
  unsigned int generateID(){return maxID; }
private:
  unordered_map<unsigned int, Account*> accounts;
  unsigned int maxID;
  vector<Account*> cemetery;
};

#endif /* Pack_hpp */
