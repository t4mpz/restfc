#pragma once

#include <stdlib.h>

typedef struct {
  int* items;
  size_t size;
} 
sizedI;

void
free_sized_i(sizedI* sized);
