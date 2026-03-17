#include <stdio.h>

int main() {
  long nc;
  // ctrl + D on STDIN will create EOF
  while (getchar() != EOF) {
    ++nc;
  }
  printf("%ld\n", nc);
}
