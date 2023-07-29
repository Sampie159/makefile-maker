#include "project_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_SIZE 256
#define MAX_PROJ_NAME 64

static void setup_files(MMaker *mmaker, const char *cwd);
static void create_directories(MMaker *mmaker, const char *cwd);
static int is_valid_language(const char *language);
static void print_help(void);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                          PUBLIC FUNCTIONS                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void setup_project(MMaker *mmaker) {
  if (!is_valid_language(mmaker->language)) {
    printf("Language not supported, use \"c\", \"cpp\" or \"cc\"\n");
    exit(1);
  }

  char cwd[MAX_SIZE];
  getcwd(cwd, MAX_SIZE);

  create_directories(mmaker, cwd);
  setup_files(mmaker, cwd);
  printf("Project %s initiated successfully.\n", mmaker->project_name);
}

MMaker *parse_args(int argc, char *argv[]) {
  char language[3] = "";
  char project_name[MAX_PROJ_NAME] = "";

  int opt;
  while ((opt = getopt(argc, argv, "l:p:h")) != -1) {
    switch (opt) {
    case 'l':
      strncpy(language, optarg, 3);
      break;
    case 'p':
      strncpy(project_name, optarg, MAX_PROJ_NAME);
      break;
    case 'h':
      print_help();
      exit(0);
    default:
      abort();
    }
  }

  if (strcmp(language, "") == 0 || strcmp(project_name, "") == 0) {
    printf("Missing arguments\n");
    print_help();
    exit(1);
  }

  MMaker *mmaker = (MMaker *)malloc(sizeof(MMaker));
  if (mmaker == NULL) {
    perror("Error allocating memory");
    exit(1);
  }
  memset(mmaker, 0, sizeof(MMaker));
  mmaker->language = language;
  mmaker->project_name = project_name;

  return mmaker;
}

void free_mmaker(MMaker **mmaker) {
  memset(*mmaker, 0, sizeof(MMaker));
  free(*mmaker);
  *mmaker = NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                          PRIVATE FUNCTIONS                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static void create_directories(MMaker *mmaker, const char *cwd) {
  // Define the project path
  char project_path[MAX_SIZE];
  snprintf(project_path, MAX_SIZE, "%s/%s", cwd, mmaker->project_name);

  // Define the source folder
  char src_dir[MAX_SIZE];
  snprintf(src_dir, MAX_SIZE, "%s/src", project_path);

  // Create the folders
  mkdir(project_path, 0777);
  mkdir(src_dir, 0777);
}

static void setup_files(MMaker *mmaker, const char *cwd) {
  char cmake_path[MAX_SIZE];
  snprintf(cmake_path, MAX_SIZE, "%s/CMakeLists.txt", cwd);
  char main_path[MAX_SIZE];
  snprintf(main_path, MAX_SIZE, "%s/src/main.c", cwd);
  char cmake_src_path[MAX_SIZE];
  snprintf(cmake_src_path, MAX_SIZE, "%s/src/CMakeLists.txt", cwd);

  FILE *cmake = fopen(cmake_path, "w");
  if (cmake == NULL) {
    perror("Error creating CMakeLists.txt");
    exit(1);
  }

  char *cmake_extra = "";
  if (strcmp(mmaker->language, "c") == 0) {
    cmake_extra = "set(CMAKE_C_STANDARD 17)\n"
                  "set(CMAKE_C_STANDARD_REQUIRED True)\n"
                  "set(CMAKE_C_FLAGS \"-Wall -Wextra -Wpedantic\")\n\n";
  }

  char cmake_content[1024];
  snprintf(cmake_content, 1024,
           "cmake_minimum_required(VERSION 3.10)\n\n"
           "project(%s)\n\n"
           "%sset(CMAKE_CXX_STANDARD 20)\n"
           "set(CMAKE_CXX_STANDARD_REQUIRED True)\n"
           "set(CMAKE_CXX_FLAGS \"-Wall -Wextra -Wpedantic\")\n\n"
           "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})\n\n"
           "add_subdirectory(src)\n",
           mmaker->project_name, cmake_extra);

  fprintf(cmake, "%s", cmake_content);
  fclose(cmake);

  FILE *main = fopen(main_path, "w");
  if (main == NULL) {
    perror("Error creating main.c");
    exit(1);
  }

  char *main_content;
  if (strcmp(mmaker->language, "c") == 0) {
    main_content = "#include <stdio.h>\n\n"
                   "int main(void) {\n"
                   "  printf(\"Hello World!\\n\');\n"
                   "\n"
                   "  return 0;\n"
                   "}\n";
  } else {
    main_content = "#include <iostream>\n\n"
                   "int main(void) {\n"
                   "  std::cout << \"Hello World!\\n\";\n"
                   "\n"
                   "  return 0;\n"
                   "}\n";
  }

  fprintf(main, "%s", main_content);
  fclose(main);

  FILE *cmake_src = fopen(cmake_src_path, "w");
  if (cmake_src == NULL) {
    perror("Error creating src/CMakeLists.txt");
    exit(1);
  }

  char *cmake_src_content;
  snprintf(cmake_src_content, 128,
           "cmake_minimum_required(VERSION 3.10)\n\n"
           "add_executable(\n"
           "  %s\n"
           "  main.%s\n"
           ")\n",
           mmaker->project_name, mmaker->language);

  fprintf(cmake_src, "%s", cmake_src_content);
  fclose(cmake_src);
}

/// Returns 1 if the language is valid, 0 otherwise
static int is_valid_language(const char *language) {
  if (strcmp(language, "c") == 0)
    return 1;
  if (strcmp(language, "cpp") == 0)
    return 1;
  if (strcmp(language, "cc") == 0)
    return 1;

  return 0;
}

static void print_help(void) { printf("Help!\n"); }
