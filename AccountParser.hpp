//
//  AccountParser.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/8/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef AccountParser_hpp
#define AccountParser_hpp

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Account.hpp"
#include "Parser.hpp"
#include "Pack.hpp"
using namespace std;
class AccountParser: public Parser{
public:
  AccountParser(string name): Parser(name){}
  //Using fileName,
  //Open the file and return a Pack object-pointer containing all the accounts
  //While reading the files, read the number of books currently being borrowed
  //And map the book updates to their account ids
  //If fileName is invalid, returns a pointer to an empty container
  Pack* buildPack(unordered_map<unsigned int, vector<string> >& initData);
private:
  Account* accountant(const string& info);
};

#endif /* AccountParser_hpp */
