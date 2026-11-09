#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  char* key;
  char* value;
  bool enabled;
} KVE;

typedef struct {
  KVE* items;
  int len;
} vKVE;

void
free_kve(KVE* kve);
