#include "../shell.h"

int main(void) {

  std::string line_string;
  char  line[128];
  char  *argv[128];
  char c = '\0';

  while (c != EOF) {
    printf("[Iterate_Shell] ");
    //gets(line); //reads the line
    getline(std::cin, line_string);
    strcpy(line, line_string.c_str()); //string to char array
    parse(line, argv);
    execute(argv);
  }
  return 0;
}
