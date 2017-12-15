//Shell class that handles inputs
#ifndef SHELL_HPP
#define SHELL_HPP
#include <iostream>
#include <string>
#include <algorithm>
#include "Manager.hpp"
class Shell{
public:
  Shell(string bookFile = "", string accountFileName = "");
  ~Shell();
  //Prompts the user 
  void prompt();
  bool getStatus() const {return status; }
private:
  Manager* librarian;
  bool status = true;
  string criteriaHelper(const vector<string>& criterion);
  //Returns whether the command string is valid and if it points to a keyword in the array.
  bool isValid(string command);
  //Prints the values mapped to the commands
  void functionMapper(string command);
  //could have used function pointers instead. But, let's keep it simple
  //Call browse
  void callBrowse();
  //Call book
  void callBook();
  //Call search
  void callSearch();
  //Call accounts
  void callAccounts();
  //Call account
  void callAccount();
  //call checkout
  void callCheckout();
  //Call renew
  void callRenew();
  //Call return
  void callReturn();
  //Call Recommend
  void callRecommend();
  //You get the idea
  void callAddb();
  void callRemoveb();
  void callAdda();
  void callRemovea();
  void callSystem();
  void callTime();
  void callExport();
  void callHelp();
  void callExit();
};
#endif
