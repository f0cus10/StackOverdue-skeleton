//
//  Parser.cpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/7/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#include "Parser.hpp"
#include <vector>
#include <string>
using namespace std;

Parser::Parser(string file){
  fileName = file;
}

vector<string> Parser::tokenizer(const string& info){
  //Make a copy of the data
  string tmp = info;
  vector<string> result;
  size_t pos = 0;
  while ((pos = tmp.find('|')) != string::npos) {
    result.push_back(tmp.substr(0,pos));
    tmp.erase(0, pos+1);
  }
  result.push_back(tmp);
  return result;
}
