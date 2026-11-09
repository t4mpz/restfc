#pragma once
#include "./cert_types.h"
#include "./kve.h"
#include <curl/curl.h>
#include <stdbool.h>
#define MAX_TYPE_CHAR_SIZE 16

typedef enum {
  APIKEY,
  AWSV4,
  BASIC,
  NOAUTH,
  HAWK,
  EDGEGRID,
  BEARER
} Request_Auth_Type;

typedef struct {
  char* path;
  char* name;
  char* version;
  char* uuid;
  char* lastEnv;
} Request_Meta;

typedef struct {
  // char type[16];
  Request_Auth_Type* authType;
  char* user;
  char* password;
  char* key;
} Request_Auth;

typedef enum {
  JSON,
  XML,
  TEXT,
  BLOB
} Request_Body_Type;

typedef struct {
  char* name;
  char* age;
  char* value;
  char* path;
  bool  secure;
  bool  subdomains;
} Request_Cookies;


typedef struct {
  char* path;
  char* password;
  char* key;
  Verify_Cert_Status vstatus;
  Verify_Cert_Host vhost;
  Verify_Cert_Peer vpeer;
} Request_Cert;


typedef struct {
  Request_Cookies* cookies;
  Request_Cert certificate;
  Request_Auth auth;
  char* body;
  Request_Body_Type btype;
  char* notes;
  char* url;
  vKVE vars;
  vKVE headers;
  char* method;
} Request;

typedef enum {
  REQ_INVALID_REQUEST,
  REQ_SUCCESS,
} Request_Errors;


typedef enum {
  REQ_VAR_NOT_FOUND_IN_BOUNDS,
  REQ_VAR_SUCCESS,
} Variable_Error;

Request_Errors
set_request(CURL* curl, Request req);


char*
apply_vars_to(
    const char* url, 
    const vKVE varPool, 
    const char* del, 
    const char* finalDelimiter,
    Variable_Error* varErr
);
