#include "builtins.h"
#include <readline/history.h>

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
  // if no directory is given, use the local directory
  if (tokens.size() < 2) {
    tokens.push_back(home());
  }

  // open the directory
  DIR* dir = opendir(tokens[1].c_str());

  // catch an errors opening the directory
  if (!dir) {
    // print the error from the last system call with the given prefix
    perror("cd error: ");

    // return error
    return 1;
  }
  char cwd[2048]; // up to 
  int err = chdir(tokens[1].c_str());
  getcwd(cwd, sizeof(cwd));
  setenv("PWD", cwd, 1);
  
  return err;
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
  if (tokens.size() < 2) {
    cout << "Echo requires an argument" << endl;
    return 1;
  }
  for(int i = 1; i < tokens.size(); i++){
    cout << tokens[i] << " ";
  }
  cout << endl;
  return 0;
}


int com_exit(vector<string>& tokens) {
  exit(0);
  return 0;
}


int com_history(vector<string>& tokens) {
  for(HIST_ENTRY *comm = previous_history(); comm != NULL; comm = previous_history()){
    cout << comm->line << endl;
  }
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

string home() {
    string varname = "HOME";
    string home;
    if (getenv(varname.c_str()) != NULL) {
        home = getenv(varname.c_str());
    }
    return home;
}
