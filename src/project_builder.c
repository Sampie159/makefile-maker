#include "project_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_SIZE 256

const char *create_directories(const char *project_name) {
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

void setup_files(const char *language, const char *project_name,
                 const char *project_path) {
  // Create Makefile
  char makefile_path[MAX_SIZE];
  snprintf(makefile_path, MAX_SIZE, "%s/Makefile", project_path);

  FILE *makefile = fopen(makefile_path, "w");

  char *compiler;
  if (strcmp(language, "c") == 0)
    compiler = "gcc";
  else
    compiler = "g++";

  fprintf(makefile,
          "CFLAGS=-Wall -Wextra -g\n"
          "CC=%s\n\n"
          "SRCDIR=src\n"
          "SRCS=${wildcard $(SRCDIR)/*.%s}\n\n"
          "OBJDIR=obj\n"
          "OBJS=${patsubst $(SRCDIR)/%%.%s, $(OBJDIR)/%%.o, $(SRCS)}\n\n"
          "BINDIR=bin\n\n"
          "all: $(BINDIR)/%s\n\n"
          "release: CFLAGS=-Wall -Wextra -DNDEBUG -pipe -march=native -O2\n"
          "release: $(BINDIR)/%s\n\n"
          "run: $(BINDIR)/%s\n"
          "\t$(BINDIR)/%s\n\n"
          "$(OBJDIR)/%%.o: $(SRCDIR)/%%.%s\n"
          "\t$(CC) $(CFLAGS) -c -o $@ $^\n\n"
          "$(BINDIR)/%s: $(OBJS)\n"
          "\t$(CC) $(CFLAGS) -o $@ $^\n\n"
          "clean:\n"
          "\trm $(OBJDIR)/*\n"
          "\trm $(BINDIR)/%s",
          compiler, language, language, project_name, project_name,
          project_name, project_name, language, project_name, project_name);

  fclose(makefile);

  // Initilize a "Hello World!"
  char main_path[MAX_SIZE];
  snprintf(main_path, MAX_SIZE, "%s/src/main.%s", project_path, language);

  FILE *main_file = fopen(main_path, "w");

  if (strcmp(language, "c") == 0) {
    fprintf(main_file, "#include <stdio.h>\n\n"
                       "int main() {\n"
                       "\tprintf(\"Hello world!\\n\");\n\n"
                       "\treturn 0;\n"
                       "}");

  } else {
    fprintf(main_file, "#include <iostream>\n\n"
                       "int main() {\n"
                       "\tstd::cout << \"Hello World!\\n\";\n\n"
                       "\treturn 0;\n"
                       "}");
  }

  fclose(main_file);
}

int is_valid_language(const char *language) {
  if (strcmp(language, "c") == 0)
    return 0;
  if (strcmp(language, "cpp") == 0)
    return 0;
  if (strcmp(language, "cc") == 0)
    return 0;

  return -1;
}

void setup_project(char **argv) {
  const char *language = argv[1];
  const char *project_name = argv[2];

  if (is_valid_language(language) == 0) {
    const char *project_path = create_directories(project_name);
    setup_files(language, project_name, project_path);
    printf("Project %s initiated successfully.\n", project_name);
  } else
    printf("Language not supported, use \"c\", \"cpp\" or \"cc\"\n");
}
