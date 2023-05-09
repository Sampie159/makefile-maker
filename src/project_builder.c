#include "project_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const char *build_folders(const char *project_name) {
  // Get current working directory
  char current_directory[256];
  getcwd(current_directory, sizeof(current_directory));
  printf("Current directory: %s\n", current_directory);

  // Create the paths
  char *project_path = (char *)malloc(256 * sizeof(char));
  char bin_dir[256];
  char obj_dir[256];
  char src_dir[256];

  // Populate the paths
  snprintf(project_path, 256, "%s/%s", current_directory, project_name);
  snprintf(bin_dir, 256, "%s/bin", project_path);
  snprintf(obj_dir, 256, "%s/obj", project_path);
  snprintf(src_dir, 256, "%s/src", project_path);

  // Create the folders
  mkdir(project_path, 0777);
  mkdir(bin_dir, 0777);
  mkdir(obj_dir, 0777);
  mkdir(src_dir, 0777);

  printf("Project path: %s\nObject dir: %s\nBinary dir: %s\nSource dir: %s\n",
         project_path, obj_dir, bin_dir, src_dir);

  return project_path;
}

void setup_c_files(const char *project_path, const char *project_name) {
  char makefile_path[256];

  snprintf(makefile_path, 256, "%s/Makefile", project_path);

  // Create Makefile
  FILE *makefile = fopen(makefile_path, "w");

  fprintf(makefile, "TEST");

  fclose(makefile);
}

void setup_cpp_files(const char *project_path, const char *project_name) {
  char makefile_path[256];

  snprintf(makefile_path, 256, "%s/Makefile", project_path);

  // Create Makefile
  FILE *makefile = fopen(makefile_path, "w");

  fprintf(makefile, "TEST");

  fclose(makefile);
}

void setup_c_project(const char *project_name) {
  const char *project_path = build_folders(project_name);
  setup_c_files(project_path, project_name);
}

void setup_cpp_project(const char *project_name) {
  const char *project_path = build_folders(project_name);
  setup_cpp_files(project_path, project_name);
}

void setup_project(char **argv) {
  const char *language = argv[1];
  const char *project_name = argv[2];

  printf("Language: %s\nProject name: %s\n", language, project_name);

  if (strcmp(language, "c") == 0)
    setup_c_project(project_name);
  else if (strcmp(language, "cc") == 0 || strcmp(language, "cpp") == 0)
    setup_cpp_project(project_name);
}
