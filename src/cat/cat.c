#include "cat.h"

int main(int argc, char **argv) {
  if (argc >= 2) {
    struct _flag flag;
    memset(&flag, 0, sizeof(flag));
    parser_flags(&flag, argc, argv);
    open_files(flag, argc, argv);
  } else {
    fprintf(stderr, "Not enough arguments\n");
  }
  return 0;
}

void parser_flags(struct _flag *flag, int argc, char **argv) {
  int opt;
  const char *short_options = "benstTEv";
  while ((opt = getopt(argc, argv, short_options)) != -1) {
    switch (opt) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->T = 1;
        break;
      case 'E':
        flag->E = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case '?':
        break;
      default:
        fprintf(stderr, "default\n");
        break;
    }
  }
}

void open_files(struct _flag flag, int argc, char **argv) {
  for (; optind < argc; optind++) {
    FILE *pfile_name;
    if ((pfile_name = fopen(argv[optind], "r")) == NULL) {
      fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
              argv[optind]);
    } else {
      printing(flag, pfile_name);
      fclose(pfile_name);
    }
  }
}

void printing(struct _flag flag, FILE *file) {
  flag.row_number = 1;
  flag.previous_sym = '\n';
  int blank_line = 0;
  while ((flag.current_sym = fgetc(file)) != EOF) {
    if (flag.previous_sym == '\n') {
      if (flag.s) {
        if (flag.current_sym == '\n') {
          if (blank_line) {
            flag.previous_sym = flag.current_sym;
            continue;
          }
          blank_line = 1;
        } else
          blank_line = 0;
      }
      if (flag.b && flag.current_sym != '\n') {
        fprintf(stdout, "%6d\t", flag.row_number);
        flag.row_number += 1;
      } else {
        if (flag.n) {
          fprintf(stdout, "%6d\t", flag.row_number);
          flag.row_number += 1;
        }
      }
    }
    if (flag.v) {
      if (flag.current_sym == '\n') {
        fprintf(stdout, "$");
      } else if (flag.current_sym < ' ') {
        fprintf(stdout, "^%c", flag.current_sym + 64);
        flag.previous_sym = flag.current_sym;
        continue;
      } else if (flag.current_sym == 127) {
        fprintf(stdout, "^?");
        flag.previous_sym = flag.current_sym;
        continue;
      }
    } else {
      if (flag.T) {
        if (flag.current_sym == '\t') {
          fprintf(stdout, "^I");
          flag.previous_sym = flag.current_sym;
          continue;
        }
      }
      if (flag.E) {
        if (flag.current_sym == '\n') {
          fprintf(stdout, "$");
        }
      }
    }
    fprintf(stdout, "%c", flag.current_sym);
    flag.previous_sym = flag.current_sym;
  }
}
