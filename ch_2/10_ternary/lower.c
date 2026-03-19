#include <stdio.h>

void lower(char s[]);

int main() {
  char text[] = "THIS WaS uPpEr casED";
  printf("%s\n", text);
  lower(text);
  printf("%s\n", text);
}

void lower(char s[]) {
  int i, c;
  i = c = 0;
  while ((c = s[i]) != '\0') {
    s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + ('a' - 'A') : s[i];
    ++i;
  }
}
