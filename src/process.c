#include <stdlib.h>
#include <curl/curl.h>
#include "processInfo.h"

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
		return curl_easy_init();
	}

	
	int makeRequest(CURL* handle, char* url, requestInformacija* p){
		if (handle == NULL){
			return 1;
		}
		//žiūrimas rezultatas requesto
		CURLcode rezultatas;
		
		//configuruojamas requestas, kad po 15 sekundžų timeoutas ir, kad persekiotu redirectionus.
		curl_easy_setopt(handle, CURLOPT_URL, url);
		curl_easy_setopt(handle, CURLOPT_TIMEOUT, 15L);
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
		
		//vykdomas requestas
		rezultatas = curl_easy_perform(handle);
		if (rezultatas == CURLE_OK){
			curl_off_t baitai;
			//perziureti..
			rezultatas = curl_easy_getinfo(handle, CURLINFO_SIZE_DOWNLOAD_T, &p->downlodedBytes);
			if (rezultatas == CURLE_OK){
			cleanHandle(handle);

			return 1;
			}
			closeHandle(handle)
			return 1;
		}
		cleanHandle(handle);
		return 0;
	}


