#include "./request.h"
#include <curl/header.h>
#include <curl/typecheck-gcc.h>
#include <curl/urlapi.h>
#include <stdio.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LVAR_DELIMITER "${"
#define EVAR_DELIMITER "#{"
#define IVAR_DELIMITER "@{"
#define FINAL_DELIMITER '}'


// https://.../${var}/${v1}/${v2u238943498328}
// var, v1 v2


typedef struct {
  int* items;
  size_t size;
} 
sizedI;


/**
 * Returns the respective positions of each delimiter found in a haystack
 * returns null if no variable was found
 * */
static sizedI
intercept_vars_to_str(const char* str, const char* del) {
  size_t haylen = strlen(str);
  size_t needlelen = strlen(del);
  int dCounter = 0;
  const char* s = strstr(str, del);
  while(s != NULL) {
    s = strstr(s, del);
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
  for (int pos = 0; pos < haylen; ++pos) {
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
  char* fdStr = strstr(haystack, finalDelimiter);
  int finalPos = fdStr - haystack;
  char* result = (char*) malloc(finalPos * sizeof(char));
  strncpy(result, &haystack[0], finalPos);
  return result;
}

char*
apply_vars_to(const char* url, const vKVE varPool, const char* del) {
  char* result = (char*) malloc(strlen(url) * sizeof(char));
  memset(result, 0, strlen(url) * sizeof(char));
  sizedI varsPos = intercept_vars_to_str(url, del);
  if (varsPos.size == 0) {
    strcpy(result, url); // no variables found in said url
    return result;
  }
  int vCounter = 0;
  int lastPos = 0;
  for(int p = 0; p < varsPos.size; ++p) {
    strncat(result, &url[lastPos], varsPos.items[p]);
    lastPos = varsPos.items[p] + strlen(del);
    
  }
  return result;
}

static KVE*
get_var_by_key(const vKVE vars, char* key) {
  for(int i = 0; i < vars.len; ++i) {
    if (strncmp(vars.items[i].key, key, strlen(key)) == 0) {
      return &vars.items[i];
    }
  }
  return NULL;
}

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
