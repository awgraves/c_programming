#include <stdio.h>
#include <string.h>

int strrindex(char source[], char searchfor[]);

int main() {
  char search[] = "foo";
  char source[] = "be there for the beets and beans"; // expect the match in the
                                                      // word 'beans'

  printf("The source is: \"%s\"\nThe search text is: \"%s\"\n", source, search);
  printf("The index match is: %d", strrindex(source, search));
}

/* strrindex finds the rightmost match of the searchfor text in the source text
 * or -1 if no match
 * */
int strrindex(char s[], char t[]) {
  int slen = strlen(s);
  int tlen = strlen(t);

  if (tlen > slen)
    return -1;

  int i, j, k;
  for (i = slen - tlen; i >= 0; --i) {
    for (j = i, k = 0; k < tlen && s[j] == t[k]; j++, k++)
      ;
    if (k == tlen)
      return i;
  }

  return -1;
}
