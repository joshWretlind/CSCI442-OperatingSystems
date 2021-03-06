#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/wait.h>
#include <fstream>

#include <readline/readline.h>
#include <readline/history.h>

#include "builtins.h"

// Potentially useful #includes (either here or in builtins.h):
//   #include <dirent.h>
//   #include <errno.h>
//   #include <fcntl.h>
//   #include <signal.h>
//   #include <sys/errno.h>
//   #include <sys/param.h>
//   #include <sys/types.h>
//   #include <sys/wait.h>
//   #include <unistd.h>

using namespace std;


// The characters that readline will use to delimit words
const char* const WORD_DELIMITERS = " \t\n\"\\'`@><=;|&{(";

// An external reference to the execution environment
extern char** environ;

// Define 'command' as a type for built-in commands
typedef int (*command)(vector<string>&);

// A mapping of internal commands to their corresponding functions
map<string, command> builtins;

// Variables local to the shell
map<string, string> localvars;






// Return a string representing the prompt to display to the user. It needs to
// include the current working directory and should also use the return value to
// indicate the result (success or failure) of the last command.
string get_prompt(int return_value) {
    string varname = "PWD";
    string prompt;
    if (getenv(varname.c_str()) != NULL) {
        prompt = getenv(varname.c_str());
    } else if (localvars.find(varname) != localvars.end()) {
        prompt = localvars.find(varname)->second;
    } else {
        prompt = "";
    }
    
    if( return_value != 0 ) {
        prompt += " （；¬＿¬) >";
    } else {
        prompt += " (^_^) >";
    }
  return prompt;
}


// Return one of the matches, or NULL if there are no more.
char* pop_match(vector<string>& matches) {
  if (matches.size() > 0) {
    const char* match = matches.back().c_str();

    // Delete the last element
    matches.pop_back();

    // We need to return a copy, because readline deallocates when done
    char* copy = (char*) malloc(strlen(match) + 1);
    strcpy(copy, match);

    return copy;
  }

  // No more matches
  return NULL;
}


// Generates environment variables for readline completion. This function will
// be called multiple times by readline and will return a single cstring each
// time.
char* environment_completion_generator(const char* text, int state) {
  // A list of all the matches;
  // Must be static because this function is called repeatedly
  static vector<string> matches;

  // If this is the first time called, construct the matches list with
  // all possible matches
  if (state == 0) {
    // TODO: YOUR CODE GOES HERE
  }

  // Return a single match (one for each time the function is called)
  return pop_match(matches);
}


// Generates commands for readline completion. This function will be called
// multiple times by readline and will return a single cstring each time.
char* command_completion_generator(const char* text, int state) {
  // A list of all the matches;
  // Must be static because this function is called repeatedly
  static vector<string> matches;

  // If this is the first time called, construct the matches list with
  // all possible matches
  if (state == 0) {
    // TODO: YOUR CODE GOES HERE
  }

  // Return a single match (one for each time the function is called)
  return pop_match(matches);
}


// This is the function we registered as rl_attempted_completion_function. It
// attempts to complete with a command, variable name, or filename.
char** word_completion(const char* text, int start, int end) {
  char** matches = NULL;

  if (start == 0) {
    rl_completion_append_character = ' ';
    matches = rl_completion_matches(text, command_completion_generator);
  } else if (text[0] == '$') {
    rl_completion_append_character = ' ';
    matches = rl_completion_matches(text, environment_completion_generator);
  } else {
    rl_completion_append_character = '\0';
    // We get directory matches for free (thanks, readline!)
  }

  return matches;
}


// Transform a C-style string into a C++ vector of string tokens, delimited by
// whitespace.
vector<string> tokenize(const char* line) {
  vector<string> tokens;
  string token;

  // istringstream allows us to treat the string like a stream
  istringstream token_stream(line);

  while (token_stream >> token) {
    tokens.push_back(token);
  }

  // Search for quotation marks, which are explicitly disallowed
  for (size_t i = 0; i < tokens.size(); i++) {

    if (tokens[i].find_first_of("\"'`") != string::npos) {
      cerr << "\", ', and ` characters are not allowed." << endl;

      tokens.clear();
    }
  }

  return tokens;
}




// Substitutes any tokens that start with a $ with their appropriate value, or
// with an empty string if no match is found.
void variable_substitution(vector<string>& tokens) {
  vector<string>::iterator token;

  for (token = tokens.begin(); token != tokens.end(); ++token) {

    if (token->at(0) == '$') {
      string var_name = token->substr(1);

      if (getenv(var_name.c_str()) != NULL) {
        *token = getenv(var_name.c_str());
      } else if (localvars.find(var_name) != localvars.end()) {
        *token = localvars.find(var_name)->second;
      } else {
        *token = "";
      }
    }
  }
}


// Examines each token and sets an env variable for any that are in the form
// of key=value.
void local_variable_assignment(vector<string>& tokens) {
  vector<string>::iterator token = tokens.begin();

  while (token != tokens.end()) {
    string::size_type eq_pos = token->find("=");

    // If there is an equal sign in the token, assume the token is var=value
    if (eq_pos != string::npos) {
      string name = token->substr(0, eq_pos);
      string value = token->substr(eq_pos + 1);

      localvars[name] = value;

      token = tokens.erase(token);
    } else {
      ++token;
    }
  }
}

int execute(const char* line);

char* convertStringToCStr(string& str){
	char* charArray = new char[str.size() + 1];
	strcpy(charArray, str.c_str());
	return charArray;
}
// Handles external commands, redirects, and pipes.
int execute_external_command(vector<string> tokens) {
  //handle !! and !N cases
  if((tokens[0].c_str())[0] == '!'){
      if((tokens[0].c_str())[1] == '!'){
        return execute(previous_history()->line);
      } 
      int numOfCommandsToGoBackTo = (tokens[0].c_str())[1] - '0';
      if(numOfCommandsToGoBackTo > 10 || numOfCommandsToGoBackTo < 0) {
	return 1;
      }
      int secondDigit = (tokens[0].c_str())[2] - '0';
      if(secondDigit > 0 && secondDigit < 10){
      	  numOfCommandsToGoBackTo = numOfCommandsToGoBackTo * 10 + secondDigit;
      }

      HIST_ENTRY *comm = previous_history();
      for(int i = 0; i < numOfCommandsToGoBackTo; i++){
            comm = previous_history();
      }
      return execute(comm->line);
  }

  bool isBackground = false;
    bool isPipe = false;
    bool isAppend = false;
    bool isOverwrite = false;
    bool isInput = false;
  for(int i = 0; i < tokens.size(); i++){
	if(tokens[i] == "<"){
	   isInput = true;
	}
	if(tokens[i] == ">"){
	   isOverwrite = true;
	}
	if(tokens[i] == ">>"){
	   isAppend = true;
	}
	if(tokens[i] == "|"){
          isPipe = true;
	}
    }
  if(tokens[tokens.size() - 1] == "&"){
    isBackground = true;
  }
  int currentPipe[2];
  if(isPipe){
    if(pipe(currentPipe) < 0){
      perror("Issue opening pipe");
      return -1;
    }
  }
  int pid = fork();
  if(pid == 0){

    vector<char*> tokenCharVector;
    tokenCharVector.resize(tokens.size() + 1); 
    transform (tokens.begin(), tokens.end(), tokenCharVector.begin(), convertStringToCStr);
    
   if(!isPipe){
	if((isInput || isOverwrite || isAppend) && !isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
	} else if((isInput || isOverwrite || isAppend) && isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
		tokenCharVector[tokens.size()-3] = NULL;
	}
	FILE *outfile;
	if(isOverwrite || isAppend){
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	  FILE *outfile;
	  if(isOverwrite){
	    outfile = freopen(fileName.c_str(), "w", stdout);
	  } else {
	    outfile = freopen(fileName.c_str(), "a", stdout);
	  }
        }
	if(isInput){
	  fstream inputFile;
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	   inputFile.open(fileName.c_str(),ios_base::in);
	   string fileContents;
	   string fileLine;
	   while(inputFile >> fileLine){
		fileContents += fileLine;
	   }
	   tokens.push_back(fileContents.c_str());
	    transform (tokens.begin(), tokens.end(), tokenCharVector.begin(), convertStringToCStr);
	}
	int err = execvp(tokens[0].c_str(), &tokenCharVector[0]);
	cout << endl;
	if(isOverwrite || isAppend){
	  fclose(outfile);
	}
	exit(err);
    } else {
	dup2(currentPipe[1],1);
	
	if((isInput || isOverwrite || isAppend) && !isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
	} else if((isInput || isOverwrite || isAppend) && isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
		tokenCharVector[tokens.size()-3] = NULL;
	}
	int i = 0;
	while(tokenCharVector[i] != "|"  && i < tokenCharVector.size()) {
	  i++;
	}
	for(i;i < tokenCharVector.size(); i++){
		tokenCharVector.pop_back();
	}
	for(int i = 0; i < tokenCharVector.size(); i++) {
	  cout << tokenCharVector[i] << endl;
	}
	FILE *outfile;
	if(isOverwrite || isAppend){
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	  FILE *outfile;
	  if(isOverwrite){
	    outfile = freopen(fileName.c_str(), "w", stdout);
	  } else {
	    outfile = freopen(fileName.c_str(), "a", stdout);
	  }
        }
	if(isInput){
	  fstream inputFile;
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	   inputFile.open(fileName.c_str(),ios_base::in);
	   string fileContents;
	   string fileLine;
	   while(inputFile >> fileLine){
		fileContents += fileLine;
	   }
	   tokens.push_back(fileContents.c_str());
	    transform (tokens.begin(), tokens.end(), tokenCharVector.begin(), convertStringToCStr);
	}
	int err = execvp(tokens[0].c_str(), &tokenCharVector[0]);
	cout << endl;
	if(isOverwrite || isAppend){
	  fclose(outfile);
	}
	exit(err);
    }
  } else {
    if(isPipe){
	//wait(NULL);
    vector<char*> tokenCharVector;
    tokenCharVector.resize(tokens.size() + 1); 
    transform (tokens.begin(), tokens.end(), tokenCharVector.begin(), convertStringToCStr);
	dup2(currentPipe[0],0);
	char buffer[1024*4];
	read(0,buffer,sizeof(buffer));
	cout << buffer;
	int j = 0;
	while(tokens[j] != "|"){
	  j++;
	}
	for(int i = 0; tokens[i] != "|"; i++){
		char* charArray = new char[tokens[i+j].size() + 1];
		strcpy(charArray, tokens[i+j].c_str());
		tokenCharVector[i] = charArray;
	}
	for(int i = j; i >= 0; i--){
		tokenCharVector.pop_back();
	} 
	if((isInput || isOverwrite || isAppend) && !isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
	} else if((isInput || isOverwrite || isAppend) && isBackground){
		tokenCharVector[tokens.size()-1] = NULL;
		tokenCharVector[tokens.size()-2] = NULL;
		tokenCharVector[tokens.size()-3] = NULL;
	}
	FILE *outfile;
	if(isOverwrite || isAppend){
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	  FILE *outfile;
	  if(isOverwrite){
	    outfile = freopen(fileName.c_str(), "w", stdout);
	  } else {
	    outfile = freopen(fileName.c_str(), "a", stdout);
	  }
        }
	if(isInput){
	  fstream inputFile;
	  string fileName = "";
	  if(!isBackground) {
	    fileName = tokens[tokens.size() -1];
	  } else {
	    fileName = tokens[tokens.size() -2];
	  }
	   inputFile.open(fileName.c_str(),ios_base::in);
	   string fileContents = "\"";
	   string fileLine;
	   while(inputFile >> fileLine){
		fileContents += fileLine;
	   }
	   fileContents += "\"";
	   tokens.push_back(fileContents.c_str());
	    transform (tokens.begin(), tokens.end(), tokenCharVector.begin(), convertStringToCStr);
	    inputFile.close();
	}
	tokenCharVector.push_back(buffer);
	int err = execvp(tokens[0].c_str(), &tokenCharVector[0]);
	cout << endl;
	if(isOverwrite || isAppend){
	  fclose(outfile);
	}
	close(currentPipe[1]);
	return err;
    }
    if(!isBackground){
      int returnValue = wait(NULL);
      if(returnValue == 0){
	return 1;
      }
    }     else {
      cout << "PID: " << pid << endl;
    } 

  }
    
  return 0;
}

// Executes a line of input by either calling execute_external_command or
// directly invoking the built-in command.
int execute_line(vector<string>& tokens, map<string, command>& builtins) {
  int return_value = 0;

  if (tokens.size() != 0) {
    map<string, command>::iterator cmd = builtins.find(tokens[0]);

    if (cmd == builtins.end()) {
      return_value = execute_external_command(tokens);
    } else {
      return_value = ((*cmd->second)(tokens));
    }
  }

  return return_value;
}

int execute(const char* line) {

      // Break the raw input line into tokens
      vector<string> tokens = tokenize(line);

      // Handle local variable declarations
      local_variable_assignment(tokens);

      // Substitute variable references
      variable_substitution(tokens);

      // Execute the line
      int return_value = execute_line(tokens, builtins);
      
      return return_value;
}

// The main program
int main() {
  // Populate the map of available built-in functions
  builtins["ls"] = &com_ls;
  builtins["cd"] = &com_cd;
  builtins["pwd"] = &com_pwd;
  builtins["alias"] = &com_alias;
  builtins["unalias"] = &com_unalias;
  builtins["echo"] = &com_echo;
  builtins["exit"] = &com_exit;
  builtins["history"] = &com_history;

  // Specify the characters that readline uses to delimit words
  rl_basic_word_break_characters = (char *) WORD_DELIMITERS;

  // Tell the completer that we want to try completion first
  rl_attempted_completion_function = word_completion;

  // The return value of the last command executed
  int return_value = 0;
  
  //Only store up to 20 previous commands
  stifle_history(20);

  // Loop for multiple successive commands 
  while (true) {

    // Get the prompt to show, based on the return value of the last command
    string prompt = get_prompt(return_value);

    // Read a line of input from the user
    char* line = readline(prompt.c_str());

    // If the pointer is null, then an EOF has been received (ctrl-d)
    if (!line) {
      break;
    }
    
    // If the command is non-empty, attempt to execute it
    if (line[0]) {


      // Break the raw input line into tokens
      vector<string> tokens = tokenize(line);

      // Handle local variable declarations
      local_variable_assignment(tokens);

      // Substitute variable references
      variable_substitution(tokens);

      // Execute the line
      return_value = execute_line(tokens, builtins);
      
      // Add this command to readline's history
      add_history(line);

    }

    // Free the memory for the input string
    free(line);
  }

  return 0;
}
