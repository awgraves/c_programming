#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEMAX 100

// returns 1 if next line read, otherwise writes empty string and returns EOF
int getnextline(char *line, int max, FILE *fp) {
  if (fgets(line, max, fp) == NULL) {
    *line = '\0'; // terminate the current string
    return EOF;
  }
  return 1;
}

// compares 2 files printing out the first line where they differ
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Must specify 2 files.\n");
    exit(1);
  }

  FILE *files[2];

  for (int i = 0; i < 2; i++) {
    if ((files[i] = fopen(argv[i + 1], "r")) == NULL) {
      printf("Error: cannot open file %s\n", argv[i + 1]);
      exit(1);
    }
  }

  char lines[2][LINEMAX];
  int ln = 0;
  while (++ln) {
    for (int i = 0; i < 2; i++) {
      getnextline(lines[i], LINEMAX, files[i]);
    }
    if (*lines[0] == '\0' && *lines[1] == '\0') {
      printf("Files are identical\n");
      break;
    }
    if ((strcmp(lines[0], lines[1])) != 0) {
      printf("First diff on line %d\n", ln);
      for (int i = 0; i < 2; i++) {
        printf("%s: %s\n", argv[i + 1], lines[i]);
      }
      break;
    }
  }

  for (int i = 0; i < 2; i++) {
    fclose(files[i]);
  }
}
