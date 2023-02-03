#include "grep.h"

int main(int argc, char **argv) {
  struct _flag flag;
  memset(&flag, 0, sizeof(flag));
  parser_flags(&flag, argc, argv);
  // open_files(flag, argc, argv);
  return 0;
}

void parser_flags(struct _flag *flag, int argc, char **argv) {
  int opt;
  const char *short_options = "e:ivclnhsf:";
  while ((opt = getopt(argc, argv, short_options)) != -1) {
    switch (opt) {
      case 'e':
        flag->patterns[flag->count_patterns] = optarg;
        flag->count_patterns += 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->regex_filex[flag->count_regex_files] = optarg;
        flag->count_regex_files += 1;
        break;
      case '?':
        break;
      default:
        fprintf(stderr, "default\n");
        break;
    }
  }
}
void open_files(struct _flag flag, int argc, char **argv) {}
void printing(struct _flag flag, FILE *file) {}