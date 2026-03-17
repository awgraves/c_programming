#include <stdio.h>

#define MAX_LINE 1000

void reverse(char text[], int len);

int main() {
  char line[MAX_LINE];
  int len, c;

  printf("Input your string: ");

  len = 0;
  while ((c = getchar()) != EOF) {
    if (len < MAX_LINE) {
      line[len] = c;
      ++len;
    }
  }

  reverse(line, len);
}

void reverse(char text[], int len) {
  putchar('\n');
  while (len >= 0) {
    putchar(text[len]);
    len--;
  }
  putchar('\n');
}
