#include "project_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_SIZE 256

const char *build_folders(const char *project_name) {
  // Get current working directory
  char current_directory[MAX_SIZE];
  getcwd(current_directory, MAX_SIZE);

  // Create the paths
  char *project_path = (char *)malloc(MAX_SIZE * sizeof(char));
  char bin_dir[MAX_SIZE];
  char obj_dir[MAX_SIZE];
  char src_dir[MAX_SIZE];

  // Populate the paths
  snprintf(project_path, MAX_SIZE, "%s/%s", current_directory, project_name);
  snprintf(bin_dir, MAX_SIZE, "%s/bin", project_path);
  snprintf(obj_dir, MAX_SIZE, "%s/obj", project_path);
  snprintf(src_dir, MAX_SIZE, "%s/src", project_path);

  // Create the folders
  mkdir(project_path, 0777);
  mkdir(bin_dir, 0777);
  mkdir(obj_dir, 0777);
  mkdir(src_dir, 0777);

  return project_path;
}

void setup_c_files(const char *project_path, const char *project_name) {
  // Create Makefile
  char makefile_path[MAX_SIZE];
  snprintf(makefile_path, MAX_SIZE, "%s/Makefile", project_path);

  FILE *makefile = fopen(makefile_path, "w");

  fprintf(makefile,
          "CFLAGS=-Wall -Wextra -g\n"
          "CC = gcc\n\n"
          "SRCDIR=src\n"
          "SRCS=${wildcard $(SRCDIR)/*.c}\n\n"
          "OBJDIR=obj\n"
          "OBJS=${patsubst $(SRCDIR)/%%.c, $(OBJDIR)/%%.o, $(SRCS)}\n\n"
          "BINDIR=bin\n\n"
          "all: $(BINDIR)/%s\n\n"
          "release: CFLAGS=-Wall -Wextra -DNDEBUG -pipe -march=native -O2\n"
          "release: $(BINDIR)/%s\n\n"
          "run: $(BINDIR)/%s\n"
          "\t$(BINDIR)/%s\n\n"
          "$(OBJDIR)/%%.o: $(SRCDIR)/%%.c\n"
          "\t$(CC) $(CFLAGS) -c -o $@ $^\n\n"
          "$(BINDIR)/%s: $(OBJS)\n"
          "\t$(CC) $(CFLAGS) -o $@ $^\n\n"
          "clean:\n"
          "\trm $(OBJDIR)/*\n"
          "\trm $(BINDIR)/%s",
          project_name, project_name, project_name, project_name, project_name,
          project_name);

  fclose(makefile);

  // Create main.c
  char main_path[MAX_SIZE];
  snprintf(main_path, MAX_SIZE, "%s/src/main.c", project_path);

  FILE *main_file = fopen(main_path, "w");

  fprintf(main_file, "#include <stdio.h>\n\n"
                     "int main() {\n"
                     "\tprintf(\"Hello world!\\n\");\n\n"
                     "\treturn 0;\n"
                     "}");

  fclose(main_file);
}

void setup_cpp_files(const char *project_path, const char *project_name) {
  // Create Makefile
  char makefile_path[MAX_SIZE];
  snprintf(makefile_path, MAX_SIZE, "%s/Makefile", project_path);

  FILE *makefile = fopen(makefile_path, "w");

  fprintf(makefile,
          "CFLAGS=-Wall -Wextra -g\n"
          "CC = g++\n\n"
          "SRCDIR=src\n"
          "SRCS=${wildcard $(SRCDIR)/*.cpp}\n\n"
          "OBJDIR=obj\n"
          "OBJS=${patsubst $(SRCDIR)/%%.cpp, $(OBJDIR)/%%.o, $(SRCS)}\n\n"
          "BINDIR=bin\n\n"
          "all: $(BINDIR)/%s\n\n"
          "release: CFLAGS=-Wall -Wextra -DNDEBUG -pipe -march=native -O2\n"
          "release: $(BINDIR)/%s\n\n"
          "run: $(BINDIR)/%s\n"
          "\t$(BINDIR)/%s\n\n"
          "$(OBJDIR)/%%.o: $(SRCDIR)/%%.cpp\n"
          "\t$(CC) $(CFLAGS) -c -o $@ $^\n\n"
          "$(BINDIR)/%s: $(OBJS)\n"
          "\t$(CC) $(CFLAGS) -o $@ $^\n\n"
          "clean:\n"
          "\trm $(OBJDIR)/*\n"
          "\trm $(BINDIR)/%s",
          project_name, project_name, project_name, project_name, project_name,
          project_name);

  fclose(makefile);

  // Create main.cpp
  char main_path[MAX_SIZE];
  snprintf(main_path, MAX_SIZE, "%s/src/main.cpp", project_path);

  FILE *main_file = fopen(main_path, "w");

  fprintf(main_file, "#include <iostream>\n\n"
                     "int main() {\n"
                     "\tstd::cout << \"Hello World!\\n\";\n\n"
                     "\treturn 0;\n"
                     "}");

  fclose(main_file);
}

void setup_c_project(const char *project_name) {
  const char *project_path = build_folders(project_name);
  setup_c_files(project_path, project_name);
  printf("Project %s initiated successfully.\n", project_name);
}

void setup_cpp_project(const char *project_name) {
  const char *project_path = build_folders(project_name);
  setup_cpp_files(project_path, project_name);
  printf("Project %s initiated successfully.\n", project_name);
}

void setup_project(char **argv) {
  const char *language = argv[1];
  const char *project_name = argv[2];

  if (strcmp(language, "c") == 0)
    setup_c_project(project_name);
  else if (strcmp(language, "cpp") == 0)
    setup_cpp_project(project_name);
  else
    printf("Language not supported, use either \"c\" or \"cpp\"\n");
}
