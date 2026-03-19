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
  int i, j, k, skip;

  i = j = k = skip = 0;
  while (s1[i] != '\0' && j < MAX_RESULT) {
    // ignore leading '-'
    if (s1[i] == '-') {
      while (s1[i] != ' ' && s1[i] != EOF && j < MAX_RESULT)
        s2[j++] = s1[i++];
      continue;
    }

    // advance leading non-alphanumeric
    if (!isalnum(s1[i])) {
      s2[j++] = s1[i++];
      continue;
    }

    // ranges
    while (s1[i + 1] == '-' &&
           ((isalpha(s1[i]) && isalpha(s1[i + 2])) ||
            (isdigit(s1[i]) && isdigit(s1[i + 2]))) &&
           !(skip = s1[i + 3] == '-') && // to handle edge case like a-b-c
           s1[i] < s1[i + 2]) {
      for (k = s1[i]; k <= s1[i + 2] && j < MAX_RESULT; ++k)
        s2[j++] = k;
      i += 3;
    }
    if (skip) {
      while (s1[i] != ' ' && s1[i] != EOF && j < MAX_RESULT)
        s2[j++] = s1[i++];
      continue;
    }

    s2[j++] = s1[i++];
  }
  s2[j] = '\0';
}
