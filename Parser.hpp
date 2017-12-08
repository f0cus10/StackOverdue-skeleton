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
using namespace std;

class Parser{
public:
  Parser(string file);
protected:
  string fileName;
  static vector<string> tokenizer(const string& info);
};

#endif /* Parser_hpp */
