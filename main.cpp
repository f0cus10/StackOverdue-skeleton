#include "Shell.hpp"
#include "Account.hpp"
#include "AccountParser.hpp"
#include "Archivist.hpp"
#include "Book.hpp"
#include "BookParser.hpp"
#include "Exporter.hpp"
#include "Manager.hpp"
#include "Pack.hpp"
#include "Parser.hpp"
#include "Shelf.hpp"
#include "Time.hpp"
int main(int argc, char* argv[]){
  //Uses the arguments to initialise a parser
  Shell* sh = nullptr;
  if(argc == 1){
    sh = new Shell();
  }
  if(argc == 2){
    sh = new Shell(argv[1]);
  }
  else if(argc == 3){
    sh = new Shell(argv[1], argv[2]);
  }
  while(sh->getStatus()){
    sh->prompt();
  }
  delete sh;
}
