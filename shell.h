#pragma once
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>

void parse(char *line, char *argv[]);
void execute(char *argv[]);