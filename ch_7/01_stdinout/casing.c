#include <ctype.h>
#include <stdio.h>
#include <string.h>

// just testing this single bit field concept out
struct {
  unsigned int is_upper : 1;
  unsigned int is_lower : 1;
} flags;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    goto bad_input; // testing out goto statement for error handling
  }

  char *type = argv[1];

  if (strcmp(type, "upper") == 0)
    flags.is_upper = 1;
  else if (strcmp(type, "lower") == 0)
    flags.is_lower = 1;

  if (!(flags.is_upper || flags.is_lower)) {
    goto bad_input; // am aware goto statements should typically be avoided
  }

  int c;
  while ((c = getchar()) != EOF)
    putchar(flags.is_upper ? toupper(c) : tolower(c));
  return 0;

bad_input:
  printf("Format: casing <upper|lower>\n");
  return 1;
}
