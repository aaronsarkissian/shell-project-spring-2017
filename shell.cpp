#include "shell.h"

struct Path {
  void show_path(){
  }
  void add_path(char* path){
  }
  void delete_path(char* path){
  }
};

void parse(char *line, char *argv[]) {

  char last_char = '\0';
  //fill the specified (space, enter, tab) chars with null char
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
        printf("%s%s%c%c%s\n", "special_char: ", give_me_color(3), last_char, *line, give_me_color(0));
      }
      else if(io_redirections(last_char, line) == 1) {
        printf("%s%s%c%s\n", "special_char: ", give_me_color(2), *line, give_me_color(0));
      }
      last_char = *line;
      line++;
    }
  }
  argv[sizeof(line)+1] = NULL; //end of arguments sentinel is NULL
}
//detection of special characters (AKA io redirections)
int io_redirections(char previous_char, char *current_char) {
  //char *temp_char;
  if((previous_char == *current_char) && special_chars(current_char)) {
    return 2;
  }
  else if ((previous_char != *current_char) && special_chars(current_char)) {
    return 1;
  }
  //return (char *) temp_char;
  return 0;
}
//single special char detection
int special_chars(char *unique) {
  if(*unique == '<' 
    || *unique == '>' 
    || *unique == '|') {
    return 1;
  }
  return 0;
}

void fork_exec(char *argv[]) {

  //execvp implementation yet, change it to execve
  int status;

  if(strcmp(argv[0], "exit") == 0) {
    _exit(0);
  }

  pid_t pid = fork(); //pid_t is better to avoid int size regardless of int size in different systems
  if(pid == 0) {
    //Child process
    //exec is execute, 'p': give the name of the program and the operating system will look for the program in the path
    if (execvp(*argv, argv) == -1){
      printf("%s%s%s\n", give_me_color(1), "Invalid command", give_me_color(0));
    }
  }
  else if(pid < 0){
    //Error forking
    printf("%s%s%s\n", give_me_color(1), "OH NO :( I am sick, can't do that", give_me_color(0));
    _exit(EXIT_FAILURE);
  }
  else {
    //Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    }
    while (!WIFEXITED(status) && !WIFSIGNALED(status)); // man wait(2)
  }
}

void get_comand(void) {

  char line[1024];
  char *argv[1024];

  printf("%s", "[oh my gosh shell] $ ");
  fgets(line, 1024, stdin);
  printf("%s%s%s\n", give_me_color(3), line, give_me_color(0));
  parse(line, argv);
  fork_exec(argv);
}

char * give_me_color(int color_index) {
  char * output;

  // 1 - for red, 2 - for green, 3 - for blue, 4 - for cyan,
  // 5 - for magenta, 0 - for default
  switch (color_index) {
    case 1:
      output = (char*)"\033[1;31m";
      break;
    case 2:
      output = (char*)"\033[1;32m";
      break;
    case 3:
      output = (char*)"\033[1;34m";
      break;
    case 4:
      output = (char*)"\033[1;36m";
      break;
    case 5:
      output = (char*)"\033[1;35m";
      break;
    case 0:
    default:
      output = (char*)"\033[0m";
  }
  return output;
}
