#include "../shell.h"

int main(void) {

  char  line[128];
  char  *argv[128];
  char c = '\0';
  //std::string ll;

  while (c != EOF) {
    printf("[Iterate_Shell] ");
    gets(line); //reads the line
    //getline(std::cin, ll);
    parse(line, argv);
    execute(argv);
  }
  return 0;
}
