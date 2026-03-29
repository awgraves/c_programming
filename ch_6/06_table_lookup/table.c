#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define DEFS_SIZE sizeof(defs) / sizeof(defs[0])
#define LOOKUPS_SIZE sizeof(lookups) / sizeof(lookups[0])

static char *defs[][2] = {{"foo", "bar"}, {"bin", "baz"}, {"blah", "uh"}};
static char *lookups[] = {"foo", "bin", "not", "blah"};

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);

int main() {

  int i = DEFS_SIZE;
  while (--i >= 0)
    install(defs[i][0], defs[i][1]);

  struct nlist *np;
  char **lp = lookups;
  for (i = LOOKUPS_SIZE; --i >= 0; lp++) {
    if ((np = lookup(*lp)) != NULL)
      printf("%s: %s\n", np->name, np->defn);
    else
      printf("%s: NOT FOUND\n", *lp);
  }
}

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

char *strdupnew(char *);

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdupnew(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else
    free((void *)np->defn); // free previous definition
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;

  return np;
}

char *strdupnew(char *s) {
  char *p;
  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0)
      return np;
  }
  return NULL;
}
