/* ht.h
 * samantha jane
 * hash table header
 */
#ifndef __HT_H__
#define __HT_H__

#include <stdlib.h>

/** key value types */
enum key_type {
  INT_KEY,
  CHARP_KEY
};

enum val_type {
  INT_VAL,
  FLT_VAL,
  CHARP_VAL,
  VOIDP_VAL
};

/**
 * hash table entry.
 *
 * stores a single entry of a hash table, containing type information,
 * key, value, and a ptr to the next entry of this key
 */
typedef struct hte {
  unsigned int key_type;
  unsigned int val_type;
  union key {
    int i;
    char* s;
  } key;
  union val {
    int i;
    float f;
    char* s;
    void* p;
  } val;
  struct hte* next;
} hte;

typedef struct ht {
  unsigned int key_type;
  unsigned int val_type;
  size_t capacity;
  size_t len;
  unsigned int dynamic : 1;
  hte* table;
} ht;

hte hte_create_int_int_entry(int key, int val);
hte hte_create_int_flt_entry(int key, float val);
hte hte_create_int_charp_entry(int key, char* val);
hte hte_create_int_voidp_entry(int key, void* val);
hte hte_create_charp_int_entry(char* key, int val);
hte hte_create_charp_flt_entry(char* key, float val);
hte hte_create_charp_charp_entry(char* key, char* val);
hte hte_create_charp_voidp_entry(char* key, void* val);

#define hte_create(key, value) _Generic ((key), \
  int:   _Generic ((value), \
    int:   hte_create_int_int_entry,   \
    float: hte_create_int_flt_entry,   \
    char*: hte_create_int_charp_entry, \
    void*: hte_create_int_voidp_entry \
  ),\
  char*: _Generic((value), \
    int:   hte_create_charp_int_entry,   \
    float: hte_create_charp_flt_entry,   \
    char*: hte_create_charp_charp_entry, \
    void*: hte_create_charp_voidp_entry \
  )) (key, value)

hte* ht_search_i(ht h, int key);
hte* ht_search_str(ht h, char* key);
#define ht_search(ht, key) _Generic ((key), \
  int : ht_search_i, char* : ht_search_str \
) (ht, key)

ht ht_alloc(size_t size, unsigned int key_type, unsigned int val_type);
ht ht_alloc_dynamic(size_t size, unsigned int key_type, unsigned int val_type);
int ht_free(ht* h);
int ht_is_full(ht h);
int ht_is_empty(ht h);
int ht_typematch(ht h, hte e);
int ht_add(ht* h, hte e);
int ht_shrink(ht* h);
void ht_print(ht h);
void hte_print(hte e);
void hte_print_chain(hte e);

#endif
