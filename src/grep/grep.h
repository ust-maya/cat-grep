#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct _flag {
  int e, i, v, c, l, n, h, s, f;
  int count_patterns;
  int count_regex_files;
  char *patterns[100];
  char *regex_filex[100];
};

void parser_flags(struct _flag *flag, int argc, char **argv);
void open_files(struct _flag flag, int argc, char **argv);
void printing(struct _flag flag, FILE *file);

#endif  // GREP_H