#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  void filecopy(FILE *, FILE *);
  char *prog = argv[0];

  if (argc == 1) // use stdin
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        return 1;
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      };
  return 0;
}

void filecopy(FILE *ifp, FILE *ofp) {
  int c;

  while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}
