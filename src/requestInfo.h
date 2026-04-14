#ifndef REQUESTINFO_H

#define REQUESTINFO_H

#include <curl/curl.h>

struct {
	curl_off_t downloadedBytes;
	curl_off_t uploadedBytes;
	double downloadSpeed;
	double uploadSpeed;
	double timeTaken;
}requestInfo

struct {
	char country[100];
	char city[100];
	char provider[100];
	char host[100]
	int id;
}serverioInfomacija;
#endif
