#include <error.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  if (argc != 2) {
    fprintf(stderr, "Must provide a file arg.");
    return 1;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", argv[1]);
    return 1;
  }

  int offset, n;
  printf("Enter a num to seek: ");
  scanf("%d", &offset);

  fseek(fp, offset, 0);
  printf("\nreading from offset %d...\n", offset);

  char c;
  while ((c = getc(fp)) != EOF)
    putc(c, stdout);

  fclose(fp);
  return 0;
}
