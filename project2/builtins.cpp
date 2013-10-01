#include "builtins.h"

using namespace std;


int com_ls(vector<string>& tokens) {
  // if no directory is given, use the local directory
  if (tokens.size() < 2) {
    tokens.push_back(".");
  }

  // open the directory
  DIR* dir = opendir(tokens[1].c_str());

  // catch an errors opening the directory
  if (!dir) {
    // print the error from the last system call with the given prefix
    perror("ls error: ");

    // return error
    return 1;
  }

  // output each entry in the directory
  for (dirent* current = readdir(dir); current; current = readdir(dir)) {
    cout << current->d_name << endl;
  }

  // return success
  return 0;
}


int com_cd(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "cd called" << endl; // delete when implemented
  return 0;
}


int com_pwd(vector<string>& tokens) {
  cout << pwd() << endl;
  return 0;
}


int com_alias(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "alias called" << endl; // delete when implemented
  return 0;
}


int com_unalias(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "unalias called" << endl; // delete when implemented
  return 0;
}


int com_echo(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "echo called" << endl; // delete when implemented
  return 0;
}


int com_exit(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "exit called" << endl; // delete when implemented
  return 0;
}


int com_history(vector<string>& tokens) {
  // TODO: YOUR CODE GOES HERE
  cout << "history called" << endl; // delete when implemented
  return 0;
}

string pwd() {
  string varname = "PWD";
    string pwd;
    if (getenv(varname.c_str()) != NULL) {
        pwd = getenv(varname.c_str());
    }
    return pwd;
}
