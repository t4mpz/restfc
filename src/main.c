#include <stdio.h>
// #include <curl/curl.h>
#include <stdlib.h>
// #include "../clay/clay.h"
// #include "../jansson/src/jansson.h"
// #include "../raylib/src/raylib.h"
#include <string.h>
#include <stdbool.h>


#include "types/request.h"
#include "types/kve.h"

// json_t json;

int main(void)
{
  KVE variable = (KVE){
    .key = "testvar",
    .value = "mudandovalor",
    .enabled = true
  };
  KVE v2 = (KVE){
    .key = "v2",
    .value = "valor2",
    .enabled = true
  };

  KVE vararr[] = {variable, v2};

  vKVE vars = (vKVE) {
    .items=vararr,
    2
  };
  const char* url_test = "https://teste.com/@{{testvar}/123/@{v2}/456/@{testvar}";
  Variable_Error varErr;

  char* parsed_url_var = apply_vars_to(url_test, vars, "@{", "}", &varErr);


  if (varErr == REQ_VAR_NOT_FOUND_IN_BOUNDS) {
    printf("something bad happened trying to parse the variables variable testvar not found\n");
    return 1;
  }

  if(parsed_url_var == NULL) {
    printf("Something really bad happened, I can't tell what\n");
    return 1;
  }

  if( strcmp(url_test, parsed_url_var) == 0) {
    printf("Couldn't find the variable name, maybe change those?\n");
    return 1;
  }

  printf("%s\n", parsed_url_var);
  free(parsed_url_var);
  return 0;
}
