#include <stdio.h>

int main() {
  int c, prev_new_line;

  prev_new_line = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      if (!prev_new_line) {
        putchar('\n');
        prev_new_line = 1;
      }
    } else {
      prev_new_line = 0;
      putchar(c);
    }
  }
}
