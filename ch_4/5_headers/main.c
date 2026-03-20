#include "calc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100

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
