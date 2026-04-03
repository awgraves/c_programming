#include <stdio.h>
#include <unistd.h>

typedef long Align; // for alignment to longest boundary

typedef union header {
  struct {
    union header *ptr; // next block if on free list
    unsigned size;     // size of this block
  } s;
  Align x; // force alignment of blocks
} Header;

void *exmalloc(unsigned nbytes);
void exfree(void *);

typedef struct person {
  char *firstname;
  char *lastname;
  unsigned int age;
} Person;

int main() {
  Person *people;

  printf("People is declared. Pointer val is %p\n", people);
  people = exmalloc(sizeof(Person) * 3);

  printf("People has been allocated. Pointer val is %p\n", people);
  Header *hp = (Header *)people - 1;
  printf("The block size for people is %d\n", hp->s.size);

  puts("");

  people[0] = (Person){"John", "Smith", 100};
  people[1] = (Person){"Jane", "Doe", 99};
  people[2] = (Person){"Bob", "Ross", 1};

  for (int i = 0; i < 3; i++)
    printf("%s %s is %d\n", people[i].firstname, people[i].lastname,
           people[i].age);

  exfree(people);

  return 0;
}

static Header base;          // empty list to begin
static Header *freep = NULL; // start of free list
static Header *morecore(unsigned);

// an example implementation of malloc
void *exmalloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    // no free list yet
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) { // big enough
      if (p->s.size == nunits) // exact size
        prevp->s.ptr = p->s.ptr;
      else { // allocate tail end
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }

    if (p == freep)
      if ((p = morecore(nunits)) == NULL)
        return NULL;
  }
}

#define NALLOC 1024

// an example of free
// put block ap in the free list
void exfree(void *ap) {
  Header *bp, *p;

  bp = (Header *)ap - 1; // point to block header
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; // freed block at start or end of arena

  if (bp + bp->s.size == p->s.ptr) {
    // join to upper nbr
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }
  freep = p;
}

static Header *morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) { // no space
    return NULL;
  }
  up = (Header *)cp;
  up->s.size = nu;
  exfree((void *)(up + 1));
  return freep;
}
