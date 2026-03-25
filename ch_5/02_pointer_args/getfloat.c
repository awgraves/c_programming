#include <ctype.h>
#include <stdio.h>

#define RESULT_MAX 2

int getch(void);
void ungetch(int);

// get next float from input into *pf
// returns 0 if not a number
// returns EOF if end of input
// return positive number if float was found
int getfloat(float *pf);

int main() {
  float result[RESULT_MAX];

  for (int n = 0; n < RESULT_MAX && getfloat(&result[n]) != EOF; n++)
    printf("Float found: %.3f\n", result[n]);
}

#define BUF_SIZE 1
int buf[BUF_SIZE]; // single char buffer
int bp = 0;

// get the next character from input
int getch(void) { return bp > 0 ? buf[--bp] : getchar(); }

// put a char into the buffer
void ungetch(int c) {
  if (bp >= BUF_SIZE) {
    printf("Error: char buff is full! Cannot put next char.\n");
    return;
  }
  buf[bp++] = c;
}

int getfloat(float *pf) {
  int c, sign;
  float tmp;

  while (isspace(c = getch())) // skip whitespace
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0; // not a number
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pf = 0; isdigit(c); c = getch())
    *pf = 10.0 * *pf + (c - '0');
  if (c == '.') {
    c = getch();
    for (tmp = 0.1; isdigit(c); c = getch(), tmp *= 0.1)
      *pf += tmp * (c - '0');
  }
  *pf *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}
