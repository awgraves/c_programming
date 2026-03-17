#include <stdio.h>

#define MAX_COLS 15 // at which col count should a line start to wrap

char linebuffer[MAX_COLS];

void flush_buffer(int end);
int find_space();
int shift_buffer(int start);

int main() {
  int c, i, j;

  printf("The max chars per line is: %d\n", MAX_COLS);

  i = 0;
  while ((c = getchar()) != EOF) {
    linebuffer[i++] = c;
    if (i >= MAX_COLS - 1) {
      // trace backwards to last space
      j = find_space();
      // flush buffer up until this point
      flush_buffer(j);
      // copy whatever remains to the beginning of the buffer
      // and set new buffer index
      i = shift_buffer(j);
    } else if (c == '\n') {
      flush_buffer(i);
      i = 0; // reset the buffer index
    }
  }
}

void flush_buffer(int end) {
  int i;
  printf("%d chars: ", end + 1);
  for (i = 0; i < end; ++i) {
    putchar(linebuffer[i]);
  }
  putchar('\n');
}

int shift_buffer(int start) {
  int i = 0;
  int j = start + 1;
  while (j < MAX_COLS) {
    linebuffer[i++] = linebuffer[j++];
  }
  return i;
}

int find_space(void) {
  int i = MAX_COLS - 1;
  while (i > 0 && linebuffer[i] != ' ')
    --i;
  if (i == 0)
    return MAX_COLS - 1; // handle cases where there is no space
  return i;
}
