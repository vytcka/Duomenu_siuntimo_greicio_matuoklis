#include <stdlib.h>
#include <curl/curl.h>
#include "requestInfo.h"
#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h>

	typedef struct memory {
  		char *response;
  		size_t size;
	}Memory;

	static size_t cb(char *data, size_t size, size_t nmemb, void *clientp){
  		size_t realsize = nmemb * size;
  		Memory *mem = (Memory *)clientp;

  		char *ptr = realloc(mem->response, mem->size + realsize + 1);
  		if(!ptr)
    		return 0; 

  		mem->response = ptr;
  		memcpy(&(mem->response[mem->size]), data, realsize);
  		mem->size += realsize;
 		mem->response[mem->size] = 0;

  	return realsize;
	}

	void initialiseCurl(){
		//užkrovimas curl bibliotekos.
		curl_global_init(CURL_GLOBAL_ALL);
	}
	int cleanHandle(CURL* handle){
		//po requesto padarymo, yra privalomas išvalymas, kad nebūtu atminties liejimo į sistemą.
		if (handle == NULL){
			return 1;
		}
		curl_easy_cleanup(handle);
		return 0;
	}

	CURL* getHandle(){
		//gavimas curl objekto pointeris.
		CURL* handle = curl_easy_init();
		if (handle){
			return handle;
		}
		return NULL;
	}

	int makeRequest(CURL* handle, requestInformacija* p){
		if (handle == NULL){
			return 2;
		}
		if (p == NULL){
			return 3;
		}
		//žiūrimas rezultatas requesto
		CURLcode rezultatas;
		
		//configuruojamas requestas, kad po 15 sekundžų timeoutas ir, kad persekiotu redirekcionus.
		curl_easy_setopt(handle, CURLOPT_URL, p->serveris.host);
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 15L);
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
		//vykdomas rekuestas
		rezultatas = curl_easy_perform(handle);
		if (rezultatas != CURLE_OK){
                	cleanHandle(handle);
                	p->error = UNABLE_TO_CONNECT_TO_SERVER;
                	return 1;
                }
		
		//perziureti..
		if(curl_easy_getinfo(handle, CURLINFO_SIZE_DOWNLOAD_T, &p->downloadedMegaBits) != CURLE_OK){
			p->error = ERROR_DOWNLOADED_SIZE_FAILED;
			cleanHandle(handle);
			return 1;
		}
		if (curl_easy_getinfo(handle, CURLINFO_SIZE_UPLOAD_T, &p->uploadedMegaBits) != CURLE_OK){
			p->error = ERROR_UPLOADED_SIZE_FAILED;
			cleanHandle(handle);
			return 1;
		}
		if (curl_easy_getinfo(handle, CURLINFO_TOTAL_TIME, &p->timeTaken)!= CURLE_OK){
			p->error = ERROR_TIME_RETRIEVAL_FAILED;
			cleanHandle(handle);
			return 1;
		}
		p->downloadSpeed = ((double)p->downloadedMegaBits * 8 /1000000) /p->timeTaken;
		p->uploadSpeed = ((double)p->uploadedMegaBits * 8/1000000)/p->timeTaken;
		cleanHandle(handle);
		p->error = NO_ERROR;
		return 0;          
	}

	char* getCountry(CURL *handle) {
		if (handle == NULL){
			return NULL;
		}
    		Memory chunk;
    		chunk.response = malloc(1);
    		chunk.size = 0;
    		chunk.response[0] = '\0';

    		const char *url = "http://ip-api.com/json/?fields=country";

    		curl_easy_setopt(handle, CURLOPT_URL, url);
    		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, cb);
    		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&chunk);
    		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 15L);
		curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 5L);
    		curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);

    		CURLcode rezultatas = curl_easy_perform(handle);
		
    		if (rezultatas != CURLE_OK) {
        		free(chunk.response);
        		return NULL;
    		}

    		cJSON *json = cJSON_Parse(chunk.response);

		if (json == NULL){
			free(chunk.response);
			return NULL;
		}

    		cJSON *country = cJSON_GetObjectItemCaseSensitive(json, "country");
		if (!cJSON_IsString(country) && !country->valuestring){
			cJSON_Delete(json);
			free(chunk.response);
			return NULL;
		}
		char* result = malloc(strlen(country->valuestring) + 1);
		if(result == NULL){
		       	return NULL;
		}
		strcpy(result, country->valuestring);

    		cJSON_Delete(json);
    		free(chunk.response);

    		return result;
	}
