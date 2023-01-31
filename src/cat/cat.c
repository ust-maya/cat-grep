#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct _cat {
  int b, e, n, s, t, T, E, v;
};

void parser_flags(struct _cat *cat, int argc, char **argv);
void dubug_info(struct _cat cat);

int main(int argc, char **argv) {
  struct _cat cat;
  memset(&cat, 0, sizeof(cat));
  parser_flags(&cat, argc, argv);
  dubug_info(cat);
  return 0;
}

void parser_flags(struct _cat *cat, int argc, char **argv) {
  int opt;
  const char *short_options = "benstTEv";
  while ((opt = getopt(argc, argv, short_options)) != -1) {
    switch (opt) {
      case 'b':
        cat->b = 1;
        break;
      case 'e':
        cat->e = 1;
        cat->v = 1;
        break;
      case 'n':
        cat->n = 1;
        break;
      case 's':
        cat->s = 1;
        break;
      case 't':
        cat->t = 1;
        cat->v = 1;
        break;
      case 'T':
        cat->T = 1;
        break;
      case 'E':
        cat->E = 1;
        break;
      case 'v':
        cat->v = 1;
        break;
      case '?':
        break;
      default:
        fprintf(stderr, "default\n");
        break;
    }
  }
}

void open_files() {}

void cat_s() {}

void dubug_info(struct _cat cat) {
  printf("b - %d\n", cat.b);
  printf("e - %d\n", cat.e);
  printf("n - %d\n", cat.n);
  printf("s - %d\n", cat.s);
  printf("t - %d\n", cat.t);
  printf("T - %d\n", cat.T);
  printf("E - %d\n", cat.E);
  printf("v - %d\n", cat.v);
}
