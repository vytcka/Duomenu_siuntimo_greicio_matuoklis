#ifndef PROCESS_H
#define PROCESS_H

#include <curl/curl.h>
#include "requestInfo.h"

typedef struct memory {
        char *response;
        size_t size;
}Memory;

static size_t cb(char *data, size_t size, size_t nmemb, void *clientp);

void initialiseCurl();

int cleanHandle(CURL* handle);

CURL* getHandle();

int makeRequest(CURL* handle,requestInformacija *p);

char* getCountry(CURL* handle);

#endif
