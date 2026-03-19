#include <stdio.h>

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    switch (c) {
    case '\t':
      printf("\\t");
      break;
    case '\n':
      printf("\\n");
      break;
    default:
      putchar(c);
    }
  }
}
