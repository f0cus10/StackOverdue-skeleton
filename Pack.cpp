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
  for(unsigned int i = 0; i < cemetery.size(); ++i){
    delete cemetery[i];
  }
  cemetery.clear();
}
//Given an account, add it to the collection
void Pack::addAccount(Account* newAccount){
  accounts[newAccount->getID()] = newAccount;
  if(maxID < newAccount->getID()){
    maxID = newAccount->getID() + 1;
  }
}
//Given a userID, add it to the graveyard
void Pack::removeAccount(unsigned int accountID){
  auto candidate = accounts.find(accountID);
  if(candidate != accounts.end()){
    cemetery.push_back(accounts[accountID]);
    accounts.erase(candidate);
  }
}
//Return a vector containing all the accounts for the sorting algorithms
vector<const Account* const> Pack::getAccounts() const {
  vector<const Account* const> tmp (accounts.size());
  for(auto iter = accounts.begin(); iter != accounts.end(); ++iter){
    tmp.push_back(iter->second);
  }
  return tmp;
}
//Return a const-pointer to the account, given accountID
Account* const Pack::getAccount(unsigned int accountID){
  return accounts[accountID];
}
