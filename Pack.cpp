//
//  Pack.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/8/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#include "Pack.hpp"
#include "Account.hpp"
#include <vector>
//Default Constructor
//Overloaded Destructor
Pack::~Pack(){
  for (auto iter = accounts.begin(); iter != accounts.end(); ++iter) {
    delete iter->second;
  }
  accounts.clear();
}
//Given an account, add it to the collection
void Pack::addAccount(Account* newAccount){
  accounts[newAccount->getID()] = newAccount;
}
//Return a vector containing all the accounts for the sorting algorithms
vector<const Account*> Pack::getAccounts() const {
  vector<const Account*> tmp (accounts.size());
  for(auto iter = accounts.begin(); iter != accounts.end(); ++iter){
    tmp.push_back(iter->second);
  }
  return tmp;
}
//Return a const-pointer to the account, given accountID
const Account* Pack::getAccount(unsigned int accountID){
  return accounts[accountID];
}
