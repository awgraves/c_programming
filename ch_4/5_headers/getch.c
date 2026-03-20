#include <stdio.h>

#define BUFSIZE                                                                \
  100 // overkill for this program (could do 1 char buffer) but is a general
      // example

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free pos in buffer

// get a (possibly pushed back) char
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

// push char back on input
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
