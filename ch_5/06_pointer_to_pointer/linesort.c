#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max lines to be sorted

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines); // return -1 if input too big
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main() {
  int nlines;

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    printf("\n\nSorted:\n");
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000 // max len of input line
int getnewline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getnewline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == 0) {
      return -1;
    } else {
      line[len - 1] = '\0'; // delete new line char
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

int getnewline(char *s, int max) {
  char *start = s;
  int i = 0;
  for (int c = getchar(); c != EOF && max > 0; max--, c = getchar()) {
    *s++ = c;
    i++;
    if (c == '\n') // still want this written to s
      break;
  }
  return i;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) // do nothing if array contains fewer than 2 elements
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf; // next free pos

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}
