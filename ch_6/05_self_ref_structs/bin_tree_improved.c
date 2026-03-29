#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLEN 100
#define MAXWORDS 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int *idx, struct tnode[]);
void quicksort(struct tnode list[], int left, int right);

int getword(char *, int);

/* Counts occurrences of words in stdin
 * prints them out in order of most occurrences */
int main() {
  struct tnode *root;
  char word[MAXWORDLEN];

  struct tnode results[MAXWORDS]; // allocate tnode array

  root = NULL;
  int count = 0;
  while (getword(word, MAXWORDLEN) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word, &count, results);

  quicksort(results, 0, count - 1);

  printf("\n");
  for (int i = 0; i < count; i++)
    printf("%d %s\n", results[i].count, results[i].word);
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

struct tnode *addtree(struct tnode *p, char *w, int *count,
                      struct tnode results[]) {
  int cond;

  if (*count >= MAXWORDS) {
    printf("ERROR: exceeded max word count\n");
    return p;
  }

  if (p == NULL) { // new word has arrived
    p = &results[(*count)++];
    p->word = strdupl(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w, count, results);
  else
    p->right = addtree(p->right, w, count, results);
  return p;
}

char *strdupl(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1); // +1 for '\0'
  if (p != NULL)
    strcpy(p, s);
  return p;
}

void quicksort(struct tnode v[], int left, int right) {
  int i, last;
  void swap(struct tnode v[], int i, int j);

  if (left >= right)
    return;
  swap(v, left, (left + right) / 2); // use the middle num as the pivot
  last = left;
  for (i = left + 1; i <= right; i++)
    if (v[i].count > v[left].count)
      swap(v, ++last, i);
  swap(v, left, last);
  quicksort(v, left, last - 1);
  quicksort(v, last + 1, right);
}

void swap(struct tnode v[], int i, int j) {
  struct tnode temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
