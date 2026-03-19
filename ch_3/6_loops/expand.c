#include <ctype.h>
#include <stdio.h>

#define MAX_RESULT 1000 // how long the expanded string can be

void expand(char s1[], char s2[]);

int main() {

  char text[] = "  2-7 a-d a-b-c \nA-Z0-9 \n-a-z\na-z-";
  char result[MAX_RESULT];

  printf("Original: %s\n", text);
  expand(text, result);
  printf("Result: %s\n", result);
}

void expand(char s1[], char s2[]) {
  int i, j, k;

  i = j = k = 0;
  while (s1[i] != '\0' && j < MAX_RESULT) {
    s2[j++] = s1[i++];

    // ranges
    while (s1[i] == '-' &&
           ((isalpha(s1[i - 1]) && isalpha(s1[i + 1])) ||
            (isdigit(s1[i - 1]) && isdigit(s1[i + 1]))) &&
           s1[i - 1] < s1[i + 1]) {
      for (k = s1[i - 1] + 1; k <= s1[i + 1] && j < MAX_RESULT; ++k)
        s2[j++] = k;
      i += 2;
    }
  }
  s2[j] = '\0';
}
