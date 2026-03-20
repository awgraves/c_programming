#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 // max size of operand or operator
#define NUMBER 0  // signal a number was found

#define MAXVAL 100 // max stack depth

int getop(char[]);
void push(double);
double pop(void);

// reverse polish calculator
// ie (1 - 2) * (4 + 5) would be entered as:
// 1 2 - 4 5 + *
int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '%':
      op2 = pop();
      push(fmod(pop(), op2));
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: cannot divide by 0\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
}

int sp = 0;         // next free stack pos
double val[MAXVAL]; // val stack

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  };
}

int getch(void);
void ungetch(int);

// get next oprator or numeric operand
int getop(char s[]) {
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-') {
    return c; // not a number
  }

  // handle minus sign vs beginning of negative number
  i = 0;
  if (c == '-') {
    if (!isdigit((c = getch()))) {
      ungetch(c);
      return '-';
    }
    s[++i] = c;
  }

  if (isdigit(c)) // collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') // collect decimal part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

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
