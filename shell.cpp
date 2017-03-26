#include "shell.h"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

struct Path {
  vector<string> paths;
  void show_path(){
    for (size_t i = 0; i < paths.size(); i++) {
      cout<<paths[i];
    }
  }
  void add_path(string path){
    bool shouldAdd = true;
    for (size_t i = 0; i < paths.size(); i++) {
      if(paths[i] == path){
        shouldAdd = false;
      }
    }
    if(shouldAdd){
      paths.push_back(path);
    }
    else{
      cout<<"The path already exists \n";
    }
  }
  void delete_path(string path){
    for (size_t i = 0; i < paths.size(); i++) {
      if(paths[i] == path){
        paths.erase(paths.begin() + i,paths.begin() + i + 1);
        break;
      }
    }
  }
};

void parse(char *line, char *argv[]) {

  char last_char = '\0';

  while(*line != '\0') {
    while(*line == ' ' 
      || *line == '\n' 
      || *line == '\t') {
      *line++ = '\0';
    }
    *argv++ = line; //saves the position
    //traverse to the end of the command
    while (*line != '\0' 
      && *line != ' ' 
      && *line != '\t' 
      && *line != '\n') {
      if (io_redirections(last_char, line) == 2) {
        cout << "special_char: " << give_me_color(3) << last_char << *line << give_me_color(0) << endl;
      }
      if(io_redirections(last_char, line) == 1) {
        cout << "special_char: " << give_me_color(2) << *line << give_me_color(0) << endl;
      }
      last_char = *line;
      line++;
    }
  }
  argv[sizeof(line)+1] = NULL; //end of arguments sentinel is NULL
}

int io_redirections(char previous_char, char *current_char) {
  //char *temp_char;
  if(previous_char == *current_char && special_chars(current_char)) {
    return 2;
  }
  else if (special_chars(current_char)) {
    return 1;
  }
  //return (char *) temp_char;
  return 0;
}

int special_chars(char *unique) {
  if(*unique == '<' 
    || *unique == '>' 
    || *unique == '|') {
    return 1;
  }
  return 0;
}

void fork_exec(char *argv[]) {

  //execvp implementation yet
  int status;

  if(strcmp(argv[0], "exit") == 0) {
    exit(0);
  }

  pid_t pid = fork(); //pid_t is better to avoid int size regardless of int size in different systems
  if(pid == -1){
    cout << "OH NO :( I am sick, can't do that";
  }
  else if(pid == 0) {
    //child
    //exec is execute, 'p': give the name of the program and the operating system will look for the program in the path
    execvp(*argv, argv);
  }
  else {
    //parent
    waitpid(pid, &status, 0);
  }
}

void get_comand(void) {

  string input_line;
  char line[1024];
  char *argv[1024];

  cout << "[oh my gosh shell] $ ";
  getline(cin, input_line);
  strcpy(line, input_line.c_str()); //string to char array converter
  cout << give_me_color(1) << line << give_me_color(0) << endl;
  parse(line, argv);
  fork_exec(argv);
}

string give_me_color(int color_index) {
  string output;

  // 1 - for red, 2 - for green, 3 - for blue, 4 - for cyan,
  // 5 - for magenta, 0 - for default
  switch (color_index) {
    case 1:
      output = "\033[1;31m";
      break;
    case 2:
      output = "\033[1;32m";
      break;
    case 3:
      output = "\033[1;34m";
      break;
    case 4:
      output = "\033[1;36m";
      break;
    case 5:
      output = "\033[1;35m";
      break;
    case 0:
    default:
      output = "\033[0m";
  }
  return output;
}
