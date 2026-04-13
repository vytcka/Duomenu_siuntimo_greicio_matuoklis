#include <stdlib.h>
#include <curl/curl.h>

	void intialiseCurl(){
		curl_global_init(CURL_GLOBAL_ALL);
	}

	CURL* getHandle(){
	return curl_easy_init();
	}

	
	int makeRequest(CURL* handle, char* url){
	if (handle == NULL){
	return 1;
	}
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
	curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_perform(handle);
	curl_easy_cleanup(handle);
	return 0;
	}


