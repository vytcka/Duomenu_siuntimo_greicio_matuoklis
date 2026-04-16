#ifndef REQUESTINFO_H

#define REQUESTINFO_H

#include <curl/curl.h>


enum klaidosInformacija {
	NO_ERROR = 0,
	ERROR_DOWNLOADED_SIZE_FAILED = 10,
	ERROR_UPLOADED_SIZE_FAILED = 20,
	ERROR_TIME_RETRIEVAL_FAILED = 30,
	UNABLE_TO_CONNECT_TO_SERVER = 40,
};

typedef struct {
	char country[100];
	char city[100];
	char provider[100];
	char host[100];
	int id;
}serverioInformacija;

typedef struct {
        serverioInformacija serveris;
        curl_off_t downloadedMegaBits;
        curl_off_t uploadedMegaBits;
        double downloadSpeed;
        double uploadSpeed;
        double timeTaken;
	enum klaidosInformacija error;
}requestInformacija;

#endif
