#pragma once
typedef enum {
  STATUS_CERT_ENABLED = 1,
  STATUS_CERT_DISABLED = 0
} Verify_Cert_Status;

typedef enum {
  HOST_CERT_ENABLED = 2,
  HOST_CERT_HISTORY = 1,
  HOST_CERT_DISABLED = 0
} Verify_Cert_Host;

typedef enum {
  PEER_CERT_ENABLED = 1,
  PEER_CERT_DISABLED = 0,
} Verify_Cert_Peer;
