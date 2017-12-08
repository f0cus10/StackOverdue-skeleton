#ifndef BOOKPARSER_HPP
#define BOOKPARSER_HPP
#include "Book.hpp"
#include "Shelf.hpp"
#include "Parser.hpp"
class BookParser : public Parser{
public:
  //Constructors
  BookParser(string file): Parser(file){}
  //Use the filename to parse the data from the the files into a shelf object
  //If files are invalid, return an empty shelf object
  Shelf* buildShelf();
private:
  //Uses info, which is one line of input from the files, to
  Book* bookWriter(const string& info);
};
#endif
