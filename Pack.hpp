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
  //Return a vector containing all the accounts
  vector<const Account*> getAccounts();
  //Return a const-pointer to the account, given accountID
  const Account* getAccount(unsigned int accountID);
private:
  unordered_map<unsigned int, Account*> accounts;
  //unordered_map<unsigned int, Account*> cemetery;
};

#endif /* Pack_hpp */