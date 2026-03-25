#include <stdio.h>
#include <string.h>

void reverse(char *t);

int main() {
  char text[] = "This should be reversed!";

  printf("Original: %s\n", text);
  reverse(text);
  printf("Reversed: %s\n", text);
}

void reverse(char *t) {
  char *j;
  int c;
  for (j = t + strlen(t) - 1; t < j; t++, j--)
    c = *t, *t = *j, *j = c;
}
