#include "./request.h"
#include <curl/header.h>
#include <curl/typecheck-gcc.h>
#include <curl/urlapi.h>
#include <stdio.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "./sizeI.h"

#define LVAR_DELIMITER "${"
#define EVAR_DELIMITER "#{"
#define IVAR_DELIMITER "@{"
#define FINAL_DELIMITER '}'



/**
 * Returns the respective positions of each delimiter found in a haystack
 * returns null if no variable was found
 * */
static sizedI
intercept_vars_to_str(const char* str, const char* del) {
  size_t haylen = strlen(str);
  size_t needlelen = strlen(del);
  if (needlelen == 0 || del == NULL) {
    return (sizedI){
      NULL,
      0
    };
  }
  int dCounter = 0;
  const char* s = strstr(str, del);
  while(s) {
    s = strstr(s, del);
    if (s !=  NULL) {
      s += strlen(del);
    }
    dCounter++;
  } 
  if (dCounter == 0) {
    return (sizedI) {
      NULL,
      0,
    };
  }
  int *result = malloc(dCounter * sizeof(int));
  int respos = 0;
  for (size_t pos = 0; pos < haylen; ++pos) {
    if (strncmp(&str[pos], del, needlelen) == 0) {
      result[respos] = pos;
      respos++;
    }
  }
  return (sizedI) {
    result,
    respos,
  };
}

static char*
extract_var_key(const char* haystack, const char* finalDelimiter) {
  const char* fdStr = strstr(haystack, finalDelimiter);
  int keysize = (fdStr - haystack);
  char* result = (char*) malloc((keysize + 1) * sizeof(char));
  memset(result, 0, keysize+1);
  strncpy(result, haystack, keysize);
  return result;
}

KVE*
get_var_value_by_key(const vKVE vars, char* key) {
  for(int i = 0; i < vars.len; ++i) {
    if (strncmp(vars.items[i].key, key, strlen(key)) == 0) {
      return &vars.items[i];
    }
  }
  return NULL;
}

char*
apply_vars_to(
    const char* url, 
    const vKVE varPool, 
    const char* del, 
    const char* finalDelimiter,
    Variable_Error* varErr
) {
  sizedI varsPos = intercept_vars_to_str(url, del);
  if (varsPos.size == 0) {
    free_sized_i(&varsPos);
    char* res = (char*) malloc((strlen(url)+1) * sizeof(char));
    strcpy(res, url);
    return res;
  }
  char* result = (char*) malloc(strlen(url) * sizeof(char));
  memset(result, 0, strlen(url) * sizeof(char));
  
  int lastPos = 0;
  for(size_t p = 0; p < varsPos.size; ++p) {
    result = (char*) realloc(result, (strlen(result) + (varsPos.items[p] - lastPos)  + 1)* sizeof(char));
    strncat(result, &url[lastPos], varsPos.items[p] - lastPos); // concats the url pos to the result until the next variable appears
    const char* varToSearch = &url[varsPos.items[p] + strlen(del)]; 
    char* varkey = extract_var_key(varToSearch, finalDelimiter);
    KVE* value = get_var_value_by_key(varPool, varkey);
    if (value == NULL) {
      if (varkey != NULL) {
        free(varkey);
      }
      free(result);
      free_sized_i(&varsPos);
      *varErr = REQ_VAR_NOT_FOUND_IN_BOUNDS;
      return NULL;
    }
    // checks the actual value of the retrieved variable
    // https://${varname}varvalue/rest/of/url
    // {8} / {7} / 8 / 12
    // with var total -> 8 + 7 + 12 = 27
    // with var value total -> 8 + 8 + 12 = 28
    // from with var to with biggest value = 27
    result = (char*) realloc(result, (strlen(result) + strlen(value->value) + 1)* sizeof(char));
    strcat(result, value->value); // adds up the variable value to the result string
    lastPos = varsPos.items[p] + strlen(varkey) + strlen(del) + strlen(finalDelimiter); // the starting pos of the variable name, the name and the final delimiter
    free(varkey);
  }
  *varErr = REQ_VAR_SUCCESS;
  free_sized_i(&varsPos);
  result = (char*) realloc(result, (strlen(result) + strlen(&url[lastPos]) + 1)* sizeof(char));
  strcat(result, &url[lastPos]);
  return result;
}


/**
static char*
header_to_str(const KVE header, const bool checkEnabled) {
  if (checkEnabled && !header.enabled) {
    return NULL;
  }
  int buf = sizeof(header.key) + sizeof(header.value) + 3; // counting header delimiter
  char* header_str = (char *) malloc(buf * sizeof(char));
  sprintf(header_str, "%s: %s", header.key, header.value);
  return header_str;
}

static Request_Errors
set_curl_headers(CURL* curl, Request req, const bool checkEnabled) {
  struct curl_slist *list = NULL;
  for ( int i = 0; i < req.headers.len; ++i) {
    KVE kHeader = req.headers.items[i];
    char* sHeader = header_to_str(kHeader, checkEnabled);
    list = curl_slist_append(list, sHeader);
  }
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
  curl_slist_free_all(list);
  return REQ_SUCCESS;
}

static CURLUcode
set_request_url(CURL* curl, Request req) {
  CURLU *url = curl_url();
  CURLUcode rc;
  rc = curl_url_set(url, CURLUPART_URL, req.url, 0);
  if (rc == 0){
    curl_easy_setopt(curl, CURLOPT_URL, url);
  }
  return rc;
}

Request_Errors
set_request(CURL* curl, Request req) {

  return REQ_SUCCESS;
}
*/
