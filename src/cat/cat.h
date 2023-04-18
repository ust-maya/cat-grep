#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct _flag {
  int b, e, n, s, t, T, E, v;
  int row_number;
  char previous_sym;
  char current_sym;
};

void parser_flags(struct _flag *cat, int argc, char **argv);
void open_files(struct _flag cat, int argc, char **argv);
void printing(struct _flag cat, FILE *file);

#endif  // CAT_H