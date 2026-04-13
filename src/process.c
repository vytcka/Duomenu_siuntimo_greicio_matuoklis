#include <stdlib.h>
#include <curl/curl.h>

	void initialiseCurl(){
		curl_global_init(CURL_GLOBAL_ALL);
	}
	int cleanHandle(CURL* handle){
		if (hadle == NULL){
			return 1;
		}
		curl_easy_cleanup(handle);
		return 0;
	}

	CURL* getHandle(){
		return curl_easy_init();
	}

	
	int makeRequest(CURL* handle, char* url){
		if (handle == NULL){
			return 1;
		}
		//žiūrimas rezultatas requesto
		Curlcode rezultatas;
		
		//configuruojamas requestas, kad po 5 sekundžų timeoutas ir, kad persekiotu redirectionus
		curl_easy_setopt(handle, CURLOPT_URL, url);
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
		
		//vykdomas requestas
		rezultatas = curl_easy_perform(handle);
		if (rezultatas != 0){
			cleanHandle(handle);
			return 1;
		}
		cleanHandle(handle);
		return 0;
	}


