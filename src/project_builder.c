#include "project_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *build_folders(char *project_name) {
  // Get current working directory
  char current_directory[256];
  getcwd(current_directory, sizeof(current_directory));
  printf("Current directory: %s\n", current_directory);

  // Create the paths
  char project_path[256];
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

void setup_c_files(char *project_path, char *project_name) {
  // TODO
}

void setup_cpp_files(char *project_path, char *project_name) {
  // TODO
}

void setup_c_project(char *project_name) { build_folders(project_name); }

void setup_cpp_project(char *project_name) { build_folders(project_name); }

void setup_project(char **argv) {
  char *language = argv[1];
  char *project_name = argv[2];

  printf("Language: %s\nProject name: %s\n", language, project_name);

  if (strcmp(language, "c") == 0)
    setup_c_project(project_name);
  else if (strcmp(language, "cc") == 0 || strcmp(language, "cpp") == 0)
    setup_cpp_project(project_name);
}
