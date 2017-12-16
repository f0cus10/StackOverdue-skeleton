//
//  Exporter.hpp
//  StackOverdue
//
//  Created by Iftikhar Khan on 12/15/17.
//  Copyright © 2017 Iftikhar Khan. All rights reserved.
//

#ifndef Exporter_hpp
#define Exporter_hpp

#include <iostream>
#include <fstream>
#include <string>
#include "Shelf.hpp"
#include "Pack.hpp"
using namespace std;

class Exporter{
public:
  //Overloaded constructor
  Exporter(string book, string account);
  //Takes in a shelf object and pack object as pointers and writes their data to bookFileName and accountFileName respectively
  void write(Shelf*&, Pack*&);
private:
  string bookFileName;
  string accountFileName;
  void bookExporter(Shelf*&);
  void accountExporter(Shelf*&, Pack*&);
};

#endif /* Exporter_hpp */
