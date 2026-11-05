#pragma once
#include <stdbool.h>

typedef struct {
  char* key;
  char* value;
  bool enabled;
} KVE;

typedef struct {
  KVE* items;
  int len;
} vKVE;
