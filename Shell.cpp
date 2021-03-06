#include "Shell.hpp"
#include "Manager.hpp"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
Shell::Shell(string bookFile, string accountFileName){
  librarian = new Manager(bookFile, accountFileName);
  for(unsigned int i = 0; i < librarian->getNonExistent().size(); ++i){
    cout << "Could not find library book with ID# " << librarian->getNonExistent()[i] << endl;
  }
}
Shell::~Shell(){
  delete librarian;
}
void Shell::prompt(){
  cout << "> ";
  string userInput;
  getline(cin, userInput);
  //Break it down
  functionMapper(userInput);
  cout << endl;
  return;
}
void Shell::functionMapper(string command){
  if(command == "EXIT"){
    callExit();
  }
  else if(command == "BROWSE"){
    callBrowse();
  }
  else if(command == "BOOK"){
    callBook();
  }
  else if(command == "SEARCH"){
    callSearch();
  }
  else if(command == "ACCOUNTS"){
    callAccounts();
  }
  else if(command == "ACCOUNT"){
    callAccount();
  }
  else if(command == "CHECKOUT"){
    callCheckout();
  }
  else if(command == "RENEW"){
    callRenew();
  }
  else if(command == "RETURN"){
    callReturn();
  }
  else if(command == "RECOMMEND"){
    callRecommend();
  }
  else if(command == "ADDB"){
    callAddb();
  }
  else if(command == "REMOVEB"){
    callRemoveb();
  }
  else if(command == "ADDA"){
    callAdda();
  }
  else if(command == "REMOVEA"){
    callRemovea();
  }
  else if(command == "SYSTEM"){
    callSystem();
  }
  else if (command == "PASS_TIME"){
    callTime();
  }
  else if (command == "EXPORT"){
    callExport();
  }
  else if(command == "HELP"){
    callHelp();
  }
  else{
    cout << "Invalid Command." << endl;
  }
}
//Call browse
void Shell::callBrowse(){
  vector<string> criterion {"title", "author", "genre", "bookid", "popularity"};
  string criteria = criteriaHelper(criterion);
  vector<string> output = librarian->browse(criteria);
  for(unsigned int i = 0; i < output.size(); ++i){
    cout << to_string(i+1) << ". " << output[i] << endl;
  }
  cout << endl;
  return;
}
//Call book
void Shell::callBook(){
  unsigned int input = idValidator("book id");
  //Then access the librarian
  if(input == 0) return;
  string output = librarian->book(input, false);
  cout << output;
}
//Call search
void Shell::callSearch(){
  vector<string> criterion {"title","author"};
  string criteria = criteriaHelper(criterion);
  string phrase = "";
  cout << "Enter the search phrase." << endl;
  cout << "> ";
  getline(cin, phrase);
  vector<string> output = librarian->search(phrase, criteria);
  for(unsigned int i = 0; i < output.size(); ++i){
    cout << to_string(i+1) << ". " << output[i] << endl;
  }
  if(output.size() == 0) cout << "No search results found.\n";
  cout << endl;
}
//Call accounts
//Could have used a function here to consolidate both Accounts and Browse, but it's already a lot complicated
void Shell::callAccounts(){
  vector<string> criterion {"name", "accountid", "checkouts"};
  string criteria = criteriaHelper(criterion);
  unordered_map<unsigned int, vector<string> > mappedValue;
  vector<string> output = librarian->accounts(criteria, mappedValue);
  for(unsigned int i = 0; i < output.size(); ++i){
    cout << i+1 << ". ";
    cout << output[i];
    cout << "\t";
    for(unsigned int j = 0; j < mappedValue[i].size(); ++j){
      cout << j+1 << ". ";
      cout << mappedValue[i][j];
    }
    cout << endl;
  }
}
//Call account
void Shell::callAccount(){
  unsigned int accountID = idValidator("account id");
  if(accountID == 0) return;
  string output = librarian->account(accountID);
  cout << output << endl;
}
//call checkout
void Shell::callCheckout(){
  unsigned int accountID = idValidator("account id");
  if(accountID == 0) return;
  unsigned int bookID = idValidator("book id");
  if(bookID == 0) return;
  
  if(!librarian->isValid(accountID, 'A')){
    cout << "AccountID# " << accountID << " not found." << endl;
    return;
  }
  else if(!librarian->isValid(bookID, 'B')){
    cout << "BookID# " << bookID << " not found." << endl;
    return;
  }
  string reason;
  if(!librarian->canBorrow(accountID, reason)){
    cout << reason << endl;
    return;
  }
  string output = librarian->book(bookID, false);
  output = output.substr(0,output.find("AVAILABLE"));
  if(librarian->checkout(bookID, accountID) == false){
    cout << "Book already is checked out." << endl;
    return;
  }
  cout << "Book successfully checked out." << endl;
  cout << output << endl;
  return;
}
//Call renew
void Shell::callRenew(){
  unsigned int accountID = idValidator("account id");
  if(librarian->isValid(accountID, 'A') == false){
    cout << "AccountID# " << accountID << " not found. " << endl;
    return;
  }
  cout << librarian->renew(accountID) << endl;
}
//Call return
void Shell::callReturn(){
  unsigned int bookID = idValidator("book id");
  if(librarian->isValid(bookID, 'B') == false){
    cout << "BookID# " << bookID << " not found. " << endl;
    return;
  }
  cout << librarian->returnBook(bookID) << endl;
  return;
}
//Call Recommend
void Shell::callRecommend(){
  unsigned int accountID = idValidator("account id");
  if(accountID == 0) return;
  if(!librarian->isValid(accountID, 'A')){
    cout << "AccountID# " << accountID << " not found. " << endl;
    return;
  }
  vector<string> choices;
  vector<string> recommendations = librarian->recommend(accountID, choices);
  //Since the output is formatted, we're not going to loop
  unsigned int ctr = 0;
  while (ctr < 3) {
    cout << "You love " << choices[ctr] << ". We Recommend: " << endl;
    if(ctr == 0){
      cout << "1. " << recommendations[0] << endl;
      cout << "2. " << recommendations[1] << endl;
    }
    else if (ctr == 1){
      cout << "1. " << recommendations[2] << endl;
      cout << "2. " << recommendations[3] << endl;
    }
    else if(ctr == 2){
      cout << "1. " << recommendations[4] << endl;
    }
    ++ctr;
  }
  cout << endl;
}
//You get the idea
void Shell::callAddb(){
  string newTitle;
  string newAuthor;
  string newGenre;
  cout << "Enter the new book's title." << endl;
  cout << "> ";
  getline(cin, newTitle);
  
  cout << "Enter the new book's author." << endl;
  cout << "> ";
  getline(cin, newAuthor);
  if(librarian->bookExists(newTitle, newAuthor)){
    cout << "Book with this title and author already exists." << endl;
    return;
  }
  
  cout << "Enter the new book's genre." << endl;
  cout << "> ";
  getline(cin, newGenre);
  cout << librarian->addBook(newTitle, newAuthor, newGenre) << endl;
  return;
}
void Shell::callRemoveb(){
  unsigned int toBeRemoved = idValidator("book id");
  if (toBeRemoved == 0) return;
  cout << librarian->removeBook(toBeRemoved) << endl;
}
void Shell::callAdda(){
  string name;
  cout << "Enter the new user's name." << endl;
  cout << "> ";
  getline(cin, name);
  cout << librarian->addAccount(name);
}
void Shell::callRemovea(){
  unsigned userID = idValidator("account id");
  if(userID == 0) return;
  if(librarian->isValid(userID, 'A')){
    cout << librarian->removeAccount(userID);
    return;
  }
  cout << "AccountID# " << userID << " not found. " << endl;
}
void Shell::callSystem(){
  cout << librarian->system() << endl;
}
void Shell::callTime(){
  unsigned int timeToTravel = idValidator("number of days to time travel");
  cout << librarian->time(timeToTravel) << endl;
}
void Shell::callExport(){
  string bookFile;
  string accountFile;
  cout << "Enter the name for the books file. (This may overwrite a file)" << endl;
  cout << "> ";
  getline(cin, bookFile);
  cout << "Enter the name for the accounts file. (This may overwrite a file)" << endl;
  cout << "> ";
  getline(cin, accountFile);
  librarian->exportData(bookFile, accountFile);
  cout << "Books data succesfully exported to \"" << bookFile << "\"." << endl;
  cout << "Accounts data successfully exported to \"" << accountFile << "\"." << endl;
}
void Shell::callHelp(){
  cout << "BROWSE: Provides the status of all the books." << endl;
  cout << "BOOK: Provides the status of a specific book." << endl;
  cout << "SEARCH: Searches for all books with a key-phrase in the title or author." << endl;
  cout << "ACCOUNTS: Provides account snapshots for all user accounts." << endl;
  cout << "ACCOUNT: Provides an account snapshot for a specific user account." << endl;
  cout << "CHECKOUT: Checks a book out to a user account." << endl;
  cout << "RENEW: Renews a checked out book. (Up to two times allowed)" << endl;
  cout << "RETURN: Returns a checked out book." << endl;
  cout << "RECOMMEND: Generates a list of recommended books for a given user." << endl;
  cout << "ADDB: Adds a new book to the library." << endl;
  cout << "REMOVEB: Removes a specific book from the library." << endl;
  cout << "ADDA: Creates a new user account in the library." << endl;
  cout << "REMOVEA: Removes a specific user account from the library." << endl;
  cout << "SYSTEM: Provides diagnostic information about the system." << endl;
  cout << "TIME: Fast forwards the system time by a specified number of days." << endl;
  cout << "EXPORT: Exports the library's books and accounts to files." << endl;
  cout << "HELP: Displays this help menu." << endl;
  cout << "EXIT: Exists the program." << endl;
}
void Shell::callExit(){
  status = false;
  cout << "Thank you for using StackOverdue!" << endl;
}
string Shell::criteriaHelper(const vector<string>& criterion){
  cout << "Entire the criteria to sort by. ";
  cout << "(";
  for(unsigned int i = 0; i < criterion.size(); ++i){
    cout << criterion[i] << ((i == criterion.size()-1)?")":"/");
  }
  cout << endl;
  //Input part
  cout << "> ";
  string input;
  getline(cin, input);
  //Search for input in the criterion
  auto iter = find(criterion.begin(), criterion.end(), input);
  if(iter == criterion.end()){
    return "Invalid Value.\n\n";
  }
  return *iter;
}
unsigned int Shell::idValidator(string type){
  cout << "Enter the " << type << " ." << endl << endl;
  cout << "> ";
  string userInput;
  getline(cin, userInput);
  unsigned int input;
  try{
    input = stoi(userInput);
  }
  catch(exception& e){
    cout << "Invalid Value." << endl << endl;
    return 0;
  }
  return input;
}
