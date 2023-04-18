#include "grep.h"

int main(int argc, char **argv) {
  if (argc >= 3) {
    struct _flag flag;
    struct _array array;
    memset(&flag, 0, sizeof(flag));
    allocate_memory(&array);
    parsing(flag, array, argc, argv);
    free_memory(&array);
  } else {
    fprintf(stderr, "not enough arguments =(\n");
  }
  return 0;
}

void allocate_memory(struct _array *array) {
  array->template = (char **)malloc(ARR_SIZE * sizeof(char *));
  array->file_name = (char **)malloc(ARR_SIZE * sizeof(char *));
  for (int i = 0; i < ARR_SIZE; i++) {
    array->template[i] = (char *)malloc(ARR_SIZE * sizeof(char));
    array->file_name[i] = (char *)malloc(ARR_SIZE * sizeof(char));
  }
}

void free_memory(struct _array *array) {
  for (int i = 0; i < ARR_SIZE; i++) {
    free(array->template[i]);
    free(array->file_name[i]);
  }
  free(array->template);
  free(array->file_name);
}

void parsing(struct _flag flag, struct _array array, int argc, char **argv) {
  int return_value;
  while (1) {
    const char *short_options = "e:ivclnhsf:o";
    return_value = getopt(argc, argv, short_options);
    if (return_value == -1) {
      break;
    }
    switch (return_value) {
      case 'e':
        flag.e = 1;
        strcpy(array.template[flag.templates_num], optarg);
        flag.templates_num += 1;
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        flag.e = 1;
        regex_file(argv, optarg, &array, &flag);
        break;
      case 'o':
        flag.o = 1;
        break;
      case '?':
        fprintf(stderr, "case '?'\n");
        break;
      default:
        fprintf(stderr, "default\n");
        break;
    }
  }

  if (flag.e == 0) {
    strcpy(array.template[flag.templates_num], argv[optind]);
    flag.templates_num += 1;
    optind += 1;
  }

  flag.files_num = argc - optind;
  for (int i = 0; i < flag.files_num; i++) {
    strcpy(array.file_name[i], argv[optind]);
    optind += 1;
  }

  openfiles(argv, flag, array);
}

void regex_file(char **argv, char *reg_file_name, struct _array *array,
                struct _flag *flag) {
  FILE *regex_file = fopen(reg_file_name, "r");
  if (regex_file == NULL) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
            reg_file_name);
  } else {
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, regex_file) != -1) {
      int tmp_len = strlen(line);
      if (tmp_len > 1) {
        if (line[tmp_len - 1] == '\n') {
          snprintf(array->template[flag->templates_num], tmp_len, "%s", line);
        } else {
          snprintf(array->template[flag->templates_num], tmp_len + 1, "%s",
                   line);
        }
      } else {
        strcpy(array->template[flag->templates_num], line);
      }
      flag->templates_num += 1;
    }
    free(line);
    fclose(regex_file);
  }
}

void openfiles(char **argv, struct _flag flag, struct _array array) {
  FILE *pfile_name;
  for (int i = 0; i < flag.files_num; i++) {
    if ((pfile_name = fopen(array.file_name[i], "r")) == NULL) {
      if (!flag.s) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                array.file_name[i]);
      }
    } else {
      grep(flag, array, pfile_name, i);
      fclose(pfile_name);
    }
  }
}

void grep(struct _flag flag, struct _array array, FILE *pfile_name,
          int index_file_name) {
  char *line = NULL;
  int line_number = 1;
  int reg_match = 1;
  int number_of_matches = 0;
  int option = 0;
  size_t len = 0;
  regex_t preg;
  regmatch_t pmatch[2];
  while ((getline(&line, &len, pfile_name)) != -1) {
    int new_line = 1;
    for (int i = 0; i < flag.templates_num; i++) {
      if (flag.i == 1) {
        option = REG_ICASE;
      } else {
        option = REG_EXTENDED;
      }
      regcomp(&preg, array.template[i], option);
      if (flag.o == 0) {
        reg_match = regexec(&preg, line, 0, 0, 0);
        if (reg_match == 0) {
          regfree(&preg);
          break;
        }
        regfree(&preg);
      } else {
        while (regexec(&preg, line, 2, pmatch, 0) == 0) {
          reg_match = 0;
          if (flag.v == 0 && flag.c == 0 && flag.l == 0) {
            if (new_line == 1) {
              if (flag.files_num > 1 && flag.h == 0) {
                fprintf(stdout, "%s:", array.file_name[index_file_name]);
              }
              if (flag.n == 1) {
                fprintf(stdout, "%d:", line_number);
              }
            }
            for (int j = pmatch->rm_so; j < pmatch->rm_eo; ++j) {
              fprintf(stdout, "%c", line[j]);
            }
            printf("\n");
          }
          for (int k = 0; k < pmatch->rm_eo; k++) {
            line[k] = ' ';
          }
          new_line = 0;
        }
        regfree(&preg);
      }
    }
    if (flag.v == 1) {
      if (reg_match == 1) {
        reg_match = 0;
      } else {
        reg_match = 1;
      }
    }
    if (reg_match == 0) {
      number_of_matches += 1;
    }
    if (reg_match == 0 && flag.l == 0 && flag.c == 0 && flag.o == 0) {
      if (flag.files_num > 1 && flag.h == 0) {
        fprintf(stdout, "%s:", array.file_name[index_file_name]);
      }
      if (flag.n == 1) {
        fprintf(stdout, "%d:", line_number);
      }
      fprintf(stdout, "%s", line);
      if (line[strlen(line) - 1] != '\n') {
        fprintf(stdout, "\n");
      }
    } else if (reg_match == 0 && flag.l == 0 && flag.c == 0 && flag.o == 1 &&
               flag.v == 1) {
      if (flag.files_num > 1 && flag.h == 0) {
        fprintf(stdout, "%s:", array.file_name[index_file_name]);
      }
      if (flag.n == 1) {
        fprintf(stdout, "%d:", line_number);
      }
      fprintf(stdout, "%s", line);
      if (line[strlen(line) - 1] != '\n') {
        fprintf(stdout, "\n");
      }
    }
    reg_match = 1;
    line_number += 1;
  }
  if (flag.c == 1) {
    if (flag.files_num > 1 && flag.h == 0) {
      fprintf(stdout, "%s:", array.file_name[index_file_name]);
    }
    if (flag.l == 1 && number_of_matches > 0) {
      number_of_matches = 1;
    }
    fprintf(stdout, "%d\n", number_of_matches);
  }
  if (flag.l == 1 && number_of_matches > 0) {
    fprintf(stdout, "%s\n", array.file_name[index_file_name]);
  }
  free(line);
}
