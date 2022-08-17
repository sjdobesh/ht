#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "ht.h"

/* entry creation implementation - generic macro controlled */

hte hte_create_int_int_entry(int key, int val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = INT_VAL;
  e.key.i = key;
  e.val.i = val;
  e.next = NULL;
  return e;
}
hte hte_create_int_flt_entry(int key, float val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = FLT_VAL;
  e.key.i = key;
  e.val.f = val;
  e.next = NULL;
  return e;
}
hte hte_create_int_charp_entry(int key, char* val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = CHARP_VAL;
  e.key.i = key;
  e.val.s = val;
  e.next = NULL;
  return e;
}
hte hte_create_int_voidp_entry(int key, void* val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = VOIDP_VAL;
  e.key.i = key;
  e.val.p = val;
  e.next = NULL;
  return e;
}
hte hte_create_charp_int_entry(char* key, int val) {
  hte e;
  e.key_type = CHARP_KEY;
  e.val_type = INT_VAL;
  e.key.s = key;
  e.val.i = val;
  e.next = NULL;
  return e;
}
hte hte_create_charp_flt_entry(char* key, float val) {
  hte e;
  e.key_type = CHARP_KEY;
  e.val_type = FLT_VAL;
  e.key.s = key;
  e.val.f = val;
  e.next = NULL;
  return e;
}
hte hte_create_charp_charp_entry(char* key, char* val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = CHARP_VAL;
  e.key.s = key;
  e.val.s = val;
  e.next = NULL;
  return e;
}
hte hte_create_charp_voidp_entry(char* key, void* val) {
  hte e;
  e.key_type = INT_KEY;
  e.val_type = VOIDP_VAL;
  e.key.s = key;
  e.val.p = val;
  e.next = NULL;
  return e;
}

/**
 * create a new hash table with a set size and key val scheme.
 *
 * @param size the initial size for the hash table
 * @param key_type enum for type of key
 * @param val_type enum for type of val
 * @return ht<key, val>
 */
ht ht_alloc(size_t size, unsigned int key_type, unsigned int val_type){
  ht h;
  errno = 0;
  h.key_type = key_type;
  h.val_type = val_type;
  h.capacity = size;
  h.table = malloc(size * sizeof(hte));
  if (!h.table) {
    errno = ENOMEM;
    h.capacity = 0;
  }
  return h;
}

/**
 * create a new hash table with a dynamic size and key val scheme.
 * all contents passed to regular ht_alloc, then dynamic flag is set.
 *
 * @param size the initial size for the hash table
 * @param key_type enum for type of key
 * @param val_type enum for type of val
 * @return ht<key, val>
 */
ht ht_alloc_dynamic(size_t size, unsigned int key_type, unsigned int val_type){
  ht h = ht_alloc(size, key_type, val_type);
  h.dynamic = 1;
  return h;
}

/**
 * frees a hash tables internal table.
 *
 * @param h hash table
 * @returns an exit code
 */
int ht_free(ht* h) {
  errno = 0;
  if (h && h->table) {
    free(h->table);
    h->capacity = 0;
    h->len = 0;
    return 0;
  } else {
    errno = EPERM;
    return 1;
  }
}

/**
 * check if hash table is full.
 *
 * @param h hash table
 * @return a boolean or -1 and set errno on error
 */
int ht_is_full(ht h) {
  errno = 0;
  if (!h.table) {
    errno = EPERM;
    return -1;
  }
  if (h.capacity == h.len) {
    return 1;
  }
  return 0;
}

/**
 * check if hash table is empty
 *
 * @param h hash table
 * @return a boolean or -1 and set errno on error
 */
int ht_is_empty(ht h) {
  errno = 0;
  if (!h.table) {
    errno = EPERM;
    return -1;
  }
  if (h.len == 0) {
    return 1;
  }
  return 0;
}

/**
 * check that a table and entry have the same key val scheme.
 *
 * @param h hash table
 * @param e hash table entry
 * @return a boolean for if the types match.
 **/
int ht_typematch(ht h, hte e) {
  return (h.key_type == e.key_type) && (h.val_type == e.val_type);
}

/**
 * print key type enum
 */
void ht_print_key_type(unsigned int key_type) {
  switch (key_type) {
    case INT_KEY:
      printf("int");
      break;
    case CHARP_KEY:
      printf("str");
      break;
  }
}

/**
 * print val type enum
 */
void ht_print_val_type(unsigned int val_type) {
  switch (val_type) {
    case INT_VAL:
      printf("int");
      break;
    case FLT_VAL:
      printf("flt");
      break;
    case CHARP_VAL:
      printf("str");
      break;
    case VOIDP_VAL:
      printf("ptr");
      break;
  }
}


/**
 * print out a hash tables data.
 * @param h hash table
 * @return void
 */
void ht_print(ht h) {
  printf("HT [\n");
  printf("  key, val : <");
  ht_print_key_type(h.key_type);
  printf(", ");
  ht_print_val_type(h.val_type);
  printf(">\n");
  printf("  capacity : %lu\n", h.capacity);
  printf("  len : %lu\n", h.len);
  printf("  ptr : %p\n", h.table);
  printf("]\n");

}

/**
 * print out a single hash table entry.
 * @param e hash table entry
 * @return void
 */
void hte_print(hte e) {
  printf("HTE [\n");
  printf("  key, val : <");
  e.key_type == INT_KEY
    ? printf("%d", e.key.i)
    : printf("%s", e.key.s);
  printf(":");
  ht_print_key_type(e.key_type);
  printf(", ");
  e.val_type == INT_VAL
    ? printf("%d", e.val.i)
    : e.val_type == FLT_VAL
      ? printf("%.2f", e.val.f)
      : e.val_type == CHARP_VAL
        ? printf("%s", e.val.s)
        : printf("%p", e.val.p);
  printf(":");
  ht_print_val_type(e.val_type);
  printf(">\n");
  printf("  next : ");
  e.next ? printf("%p\n", e.next) : printf("NULL\n");
  printf("]\n");
}

void hte_print_chain(hte e) {
  printf("CHAIN [\n");
  hte_print(e);
  while (e.next) {
    hte_print(*e.next);
    e = *e.next;
  }
  printf("]\n");

}
/* search implementation - generic macro controlled */

hte* ht_search_i(ht h, int key) {
  unsigned int i;
  errno = 0;
  if (!h.table) {
    errno = EPERM;
    return NULL;
  }
  for (i = 0; i < h.len; i++) {
    if (h.table[i].key.i == key) {
      return &(h.table[i]);
    }
  }
  return NULL;
}

hte* ht_search_str(ht h, char* key) {
  unsigned int i;
  errno = 0;
  if (!h.table) {
    errno = EPERM;
    return NULL;
  }
  for (i = 0; i < h.len; i++) {
    if (strcmp(h.table[i].key.s, key)) {
      return &(h.table[i]);
    }
  }
  return NULL;
}

/**
 * add an entry to a hash table.
 * will auto expand if hash table has `.dynamic`.
 *
 * @param h hash table ptr
 * @param e hash table entry
 * @return an exit code
 */
int ht_add(ht* h, hte e) {
  hte* query;
  errno = 0;
  if (!h) {
    errno = EPERM;
    return 1;
  }
  if (!ht_typematch(*h, e)) {
    fprintf(stderr, "ERROR > key, val type mismatch\n");
    errno = EPERM;
    return 1;
  }
  if (ht_is_full(*h)) {
    if (!h->dynamic) {
      errno = ENOMEM;
      return 1;
    }
    h->table = realloc(h->table, sizeof(hte) * ++(h->capacity));
    if (!h->table) {
      errno = EPERM;
      return 1;
    }
  }
  /* query existing chains before we insert */
  query = (e.key_type == INT_KEY
    ? ht_search_i(*h, e.key.i)
    : ht_search_str(*h, e.key.s));
  /* append to table and increment count */
  h->table[h->len++] = e;
  /* search if there is a key chain to add onto */
  if (query) {
    while (query->next) {
      query = query->next;
    };
    query->next = &(h->table[h->len-1]);
  }
  return 0;
}

/**
 * shrink container to remove wasted space.
 *
 * @param h hash table ptr to shrink.
 * @return an exit code.
 */
int ht_shrink(ht* h) {
  errno = 0;
  if (!h || !h->table) {
    errno = EPERM;
    return 1;
  }
  h->table = realloc(h->table, sizeof(hte) * h->len);
  if (!h->table) {
    errno = EPERM;
    h->capacity = 0;
    h->len = 0;
    return 1;
  }
  h->capacity = h->len;
  return 0;
}
