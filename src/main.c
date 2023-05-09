#include "project_builder.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3)
    printf("Incorrect usage, please run something like this:\nmmaker "
           "<language> <project-name>");
  else {
    setup_project(argv);
  }

  return 0;
}
