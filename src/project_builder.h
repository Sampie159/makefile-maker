#pragma once

typedef struct {
  char *language;
  char *project_name;
} MMaker;

void    setup_project(MMaker *mmaker) __attribute__((nonnull));
MMaker *parse_args(int argc, char *argv[])
    __attribute__((malloc, returns_nonnull));
