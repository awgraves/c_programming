#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

int main() {
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treeprint(root);
  return 0;
}

int getch(void);
void ungetch(int);

int getword(char *word, int lim) {
  int c;
  char *w = word;
  while (isspace((c = getch())) || c == '\n')
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  while (--lim > 0 && isalnum(*w++ = getch()))
    ;
  ungetch(*--w);
  *w = '\0';

  return *word;
}

#define BUFFSIZE 1
int bp = 0;
char buff[BUFFSIZE];

int getch(void) { return bp > 0 ? buff[bp--] : getchar(); }

void ungetch(int c) {
  if (bp >= BUFFSIZE) {
    printf("Error: buffer is full\n");
    return;
  }
  buff[bp++] = c;
}

struct tnode *talloc(void);
char *strdupl(char *);

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) { // new word has arrived
    p = talloc();
    p->word = strdupl(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  return p;
}

void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdupl(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1); // +1 for '\0'
  if (p != NULL)
    strcpy(p, s);
  return p;
}
