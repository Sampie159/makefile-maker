#include "project_builder.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  MMaker *mmaker = parse_args(argc, argv);

  setup_project(mmaker);

  return 0;
}
