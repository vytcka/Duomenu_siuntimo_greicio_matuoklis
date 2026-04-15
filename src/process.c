#include <stdlib.h>
#include <curl/curl.h>
#include "requestInfo.h"

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
		handle = curl_easy_init();
		if (handle){
			return handle;
		}
		return NULL;
	}

	
	int makeRequest(CURL* handle, char* url, requestInformacija* p){
		if (handle == NULL){
			return 2;
		}
		if (p == NULL){
			return 3;
		}
		//žiūrimas rezultatas requesto
		CURLcode rezultatas;
		
		//configuruojamas requestas, kad po 15 sekundžų timeoutas ir, kad persekiotu redirekcionus.
		curl_easy_setopt(handle, CURLOPT_URL, url);
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 15L);
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(handle, CURLOPT_UPLOAD,  1L);
		//vykdomas rekuestas
		rezultatas = curl_easy_perform(handle);
		if (rezultatas != CURLE_OK){
                	cleanHandle(handle);
                	p->error = UNABLE_TO_CONNECT_TO_SERVER;
                	return 1;
                }
		
		//perziureti..
		if(curl_easy_getinfo(handle, CURLINFO_SIZE_DOWNLOAD_T, &p->downloadedBytes) != CURLE_OK){
			p->error = ERROR_DOWNLOADED_SIZE_FAILED;
			cleanHandle(handle);
			return 1;
		}
		if (curl_easy_getinfo(handle, CURLINFO_SIZE_UPLOAD_T, &p->uploadedBytes) != CURLE_OK){
			p->error = ERROR_UPLOADED_SIZE_FAILED;
			cleanHandle(handle);
			return 1;
		}
		if (curl_easy_getinfo(handle, CURLINFO_TOTAL_TIME, &p->timeTaken)!= CURLE_OK){
			p->error = ERROR_TIME_RETRIEVAL_FAILED;
			cleanHandle(handle);
			return 1;
		}
		p->downloadSpeed = ((double)p->downloadedBytes * 8 /1000000) /p->timeTaken;
		p->uploadSpeed = ((double)p->uploadedBytes * 8/1000000)/p->timeTaken;
		cleanHandle(handle);
		p->error = NO_ERROR;
		return 0;
		
		                
	}


