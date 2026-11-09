#include "./kve.h"

void
free_kve(KVE* kve) {
  free(kve->value);
  free(kve->key);
  kve->value = NULL;
  kve->key = NULL;
  kve->enabled = false;
}
