#include <stdio.h>

#define MAXLINE 1000
#define MAXNUMS 100

void printnums(int v[], int len);
void quicksort(int v[], int left, int right);

int numbers[MAXNUMS];

int getnums(int v[], int maxints);

int main() {
  printf("Enter your numbers separated by spaces: ");
  int count = getnums(numbers, MAXNUMS);

  printf("%10s", "\nOriginal: ");
  printnums(numbers, count);
  puts("");

  quicksort(numbers, 0, count - 1);

  printf("%10s", "Sorted: ");
  printnums(numbers, count);
}

int getnums(int v[], int maxints) {
  char line[MAXLINE];
  fgets(line, MAXLINE, stdin);

  int d, i, n;
  char *lineptr = line;
  int *vp = v;
  while ((i = sscanf(lineptr, "%d%n", &d, &n)) > 0 && --maxints > 0) {
    lineptr += n; // advance for scanf
    *vp++ = d;
  }

  return vp - v;
}

void printnums(int v[], int len) {
  int *np = v;
  while (--len >= 0)
    printf(len > 0 ? "%d, " : "%d", *np++);
}

void quicksort(int v[], int left, int right) {
  void swap(int v[], int i, int j);

  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);

  int last = left;
  for (int i = left + 1; i <= right; i++) {
    if (v[i] < v[left])
      swap(v, i, ++last);
  }
  swap(v, left, last);

  quicksort(v, left, last - 1);
  quicksort(v, last + 1, right);
}

void swap(int v[], int i, int j) {
  int temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
