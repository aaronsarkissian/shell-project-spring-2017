#pragma once
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>

void get_comand(void);
void parse(char *line, char *argv[]);
void fork_exec(char *argv[]);
int special_chars(char *unique);
int io_redirections(char last_char, char *special_char); //change return type to char*
struct Path;
std::string give_me_color(int);
