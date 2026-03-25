#include <stdio.h>
#include <string.h>

// returns 1 if t occurs at end of s,
// otherwise returns 0
int strend(char *s, char *t);

int main() {
  char str[] = "This is the example sentence.";
  char t1[] = "ntence.";
  char t2[] = "foo";

  printf("The text is: %s\n", str);
  printf("The result of \"%s\" is %d\n", t1, strend(str, t1));
  printf("The result of \"%s\" is %d\n", t2, strend(str, t2));
}

int strend(char *s, char *t) {
  int slen = strlen(s);
  int tlen = strlen(t);
  if (tlen > slen)
    return 0;
  for (s += slen - tlen; *s == *t; s++, t++)
    if (*s == '\0')
      return 1;
  return 0;
}
