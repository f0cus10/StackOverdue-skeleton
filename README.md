## Assignment 3 - StackOverdue

## __StackOverdue__ ## 
StackOverdue is a library management system with export-import, time travel and overdue book tracking capabilites

## __StackOverdue Interface__ ##
The program is executed via a shell, so only the shell's COMMANDS and API are listed (read didn't have time). 

## __Shell Commands__ ##
1. `BROWSE`: Provides the status of all the books.
2. `BOOK`: Provides the status of a specific book.
3. `SEARCH`: Searches for all books with a key-phrase in the title or author.
4. `ACCOUNTS`: Provides account snapshots for all user accounts.
5. `ACCOUNT`: Provides an account snapshot for a specific user account.
6. `CHECKOUT`: Checks a book out to a user account.
7. `RENEW`: Renews a checked out book. (Up to two times allowed)
8. `RETURN`: Returns a checked out book.
9. `RECOMMEND`: Generates a list of recommended books for a given user.
10. `ADDB`: Adds a new book to the library.
11. `REMOVEB`: Removes a specific book from the library.
12. `ADDA`: Creates a new user account in the library.
13. `REMOVEA`: Removes a specific user account from the library.
14. `SYSTEM`: Provides diagnostic information about the system.
15. `TIME`: Fast forwards the system time by a specified number of days.
16. `EXPORT`: Exports the library's books and accounts to files.
17. `HELP`: Displays this help menu.
18. `EXIT`: Exists the program.

## __Shell Interface__ ##

1. `void prompt()`: Prompts the user for an input and processes it
2. `bool getStatus()`: Returns false when the user inputs 'EXIT' into it.

## Compile, Run & Clean ##
To compile the project:
```bash
$ git clone https://github.com/CSCI235-Ayzman/f0cus10-assignment3-StackOverdue.git
$ make
```
After Compilation is successful, run it using:
```bash
$ ./StackOverdue <Books File Name> <Accounts File Name>
```
If no files are provided, no default files will be used

To clean up, run:
```bash
$ make clean
```
## __Extra Features(read Bugs & Limitations)__ ##
1. Although `RECOMMEND` has been checked for the `NULL` case, there maybe unexpected crash when the book recommendation is empty
2. Input validation only happens at the `Shell` class. All other classes require validated input
