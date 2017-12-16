//
//  Parser.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/7/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Parser{
public:
  Parser(string file);
  static vector<string> tokenizer(const string& info);
protected:
  string fileName;
};

#endif /* Parser_hpp */
