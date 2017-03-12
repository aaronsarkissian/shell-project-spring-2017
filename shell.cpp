#include "shell.h"

/*
Because we are using pointer we should handle how it will parse the strings.
So, it reads the line until hits a non empty character, saves the position
into argv and skip the rest.
*/
void parse(char *line, char *argv[]) {
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
      line++;
    }
  }
  //strncpy(argv[lastIndex], "\0", 1); //curently crashs
}

void execute(char *argv[]) {
  int status;
  //compare two strings. if equal returns 0
  if (strcmp(argv[0], "exit") == 0) {
    exit(0); //command for exiting from shell
  }
  //create a new child process
  if (fork() == 0) {
    execvp(*argv, argv); //instead of execve
  }
  //wait until current process finishes its job
  else {
    waitpid(-1, &status, 0);
  }
}
