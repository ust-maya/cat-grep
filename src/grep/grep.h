#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 1000

struct _flag {
  int e, i, v, c, l, n, h, s, f, o;
  int files_num;
  int templates_num;
};

struct _array {
  char **template;
  char **file_name;
};

void allocate_memory(struct _array *array);
void free_memory(struct _array *array);
void parsing(struct _flag flag, struct _array array, int argc, char **argv);
void regex_file(char **argv, char *reg_file_name, struct _array *array,
                struct _flag *flag);
void openfiles(char **argv, struct _flag flag, struct _array array);
void grep(struct _flag flag, struct _array array, FILE *pfile_name,
          int index_file_name);
#endif  // GREP_H