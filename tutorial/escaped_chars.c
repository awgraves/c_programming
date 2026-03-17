#include <stdio.h>

int main() {
  int c, had_blank;

  had_blank = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (!had_blank) {
        putchar(c);
        had_blank = 1;
      }
      continue;
    }
    had_blank = 0;

    if (c == '\t') {
      printf("\\t");
    } else if (c == '\\') {
      printf("\\\\");
    } else {
      putchar(c);
    }
  }
}
