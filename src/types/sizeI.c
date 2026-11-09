#include "./sizeI.h"

void
free_sized_i(sizedI* sized) {
  free(sized->items);
  sized->items = NULL;
  sized->size = 0;
}
