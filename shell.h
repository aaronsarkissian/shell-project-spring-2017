#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_comand(void);
void parse(char *line, char *argv[]);
void fork_exec(char *argv[]);
int special_chars(char *unique);
int io_redirections(char last_char, char *special_char); //change return type to char*
struct Path;
char * give_me_color(int);
