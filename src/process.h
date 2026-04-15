#ifndef PROCESS_H
#define PROCESS_H

#include <curl/curl.h>
#include "requestInfo.h"

void initialiseCurl();

int cleanHandle(CURL* handle);

CURL* getHandle();

int makeRequest(CURL* handle, char* url, requestInformacija* p);

#endif
