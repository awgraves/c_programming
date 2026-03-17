#include <stdio.h>

#define MAX_LENGTH 10 // how long of a word we count

int main() {
  int i, c, wl;
  int wlc[MAX_LENGTH];

  for (i = 0; i < MAX_LENGTH; ++i) {
    wlc[i] = 0;
  }

  printf("Enter your text, then ctrl + d when finished\n");
  wl = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n' || c == ' ' || c == '\t') {
      if (wl > 0 && wl < MAX_LENGTH) {
        ++wlc[wl - 1]; // account for zero indexing
        wl = 0;
      }
    } else {
      wl++;
    }
  }

  printf("\n\nWord lengths histogram [horizontal]:\n");
  for (i = 0; i < MAX_LENGTH; ++i) {
    printf("%d ", i + 1); // account for zero indexing
    int j;
    for (j = 0; j < wlc[i]; ++j) {
      printf("#");
    }
    printf("\n");
  }

  printf("\n[Vertical]:\n");
  int graph_height = 0;
  for (i = 0; i < MAX_LENGTH; ++i) {
    if (wlc[i] > graph_height)
      graph_height = wlc[i];
  }

  int row = graph_height;
  while (row > 0) {
    for (i = 0; i < MAX_LENGTH; ++i) {
      if (wlc[i] >= row) {
        putchar('#');
      } else {
        putchar(' ');
      }
      putchar('\t'); // little spacing in between vertical cols
    }
    --row;
    printf("\n");
  }

  for (i = 0; i < MAX_LENGTH; i++) {
    printf("%d\t", i + 1);
  }
}
