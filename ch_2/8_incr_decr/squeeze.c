#include <stdio.h>

#define TRUE 1
#define FALSE 0

char text[] = "This is the line with stuff to delete";
char deletions[] = "il"; // i and l chars

void printlist(char l[]);
void squeeze(char s1[], char s2[]);

int main() {
  printf("The original text: \"%s\"\n", text);
  printf("The letters to remove: ");
  printlist(deletions);
  printf("\n\n");

  squeeze(text, deletions);
  printf("%s\n", text);
}

void printlist(char l[]) {
  int i = 0;
  while (l[i] != '\0') {
    printf("%c ", l[i]);
    ++i;
  }
}

void squeeze(char s1[], char s2[]) {
  int i, j, k, skip;

  i = j = k = 0;
  while (s1[i] != '\0') {
    skip = FALSE;
    for (k = 0; s2[k] != '\0'; ++k) {
      if (s1[i] == s2[k])
        skip = TRUE;
    }

    if (skip)
      i++;
    else
      s1[j++] = s1[i++];
  }
  s1[j] = '\0';
}
