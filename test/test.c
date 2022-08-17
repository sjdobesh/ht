#include "../src/ht.h"

int main() {
  ht h;
  h = ht_alloc(100, INT_KEY, INT_VAL);
  ht_add(&h, hte_create(1, 1));
  ht_add(&h, hte_create(1, 2));
  ht_add(&h, hte_create(1, 3));
  hte_print_chain(h.table[0]);
  return 0;
}
