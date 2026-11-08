#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include "../clay/clay.h"
#include "../jansson/src/jansson.h"
#include "../raylib/src/raylib.h"
#include <string.h>

// json_t json;

int main(void)
{
  char haystack[] = "${testefinal}";
  char finalDelimiter[] = "}";
  char* fdStr = strstr(haystack, finalDelimiter);
  int finalPos = fdStr - haystack;
  char* result = (char*) malloc(finalPos * sizeof(char));
  strncpy(result, &haystack[0], finalPos);
  printf("%s\n", result);
  char url[] = "https://testing/testingvar/${variable}/will continue printing?";
  char del[] = "${";

  char * first_occourrence = strstr(url, del);
  printf("%s", first_occourrence);
  if (first_occourrence) {
    printf("%s", first_occourrence);
  }
  else {
    printf("smthgin wrong");
    return -1;
  }
  return 0;
}
