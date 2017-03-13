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
int special_char(char *special_char); //return type should be changed
struct Path;
std::string give_me_color(int);
