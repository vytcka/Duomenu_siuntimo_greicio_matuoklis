#include "requestInfo.h"
#include "parser.h"
#include "process.h"
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void downloadTest(CURL* handle){

}


int main(int argc, char** argv){
	//  -a - automatizuotas testas, viskas integruota, lokacija programos naudojimo
	//  -d - download testas
	//  -u - upload test
	//  -s find best server.
	//  -l location
	//  veiks kaip moduliai, bus skirting moduliai ir naudotojas gali pasimiti iki 5 moduliu, 
	
	//flags...
	bool a = false;
	bool d = false;
	bool u = false;
	bool s = false;
	bool l = false;
	cJSON* iterator = NULL;

	printf("argc = %d\n", argc);
	for (int i = 0; i<argc; i++){
	puts(argv[i]);
	}
	//Json failas perskaitomas
        char* buff = readData();
	
	if (buff ==NULL){
		return 1;
	}
	// convertuojamas i cJSON objekta.
        cJSON* pntr = parseJSON(buff);
	if (pntr == NULL){
		printf("ERROR: nutiko klaida apdorojant JSON failą.");
		return 1;
	}
	free(buff);
	buff = NULL;
	
	// gaunamas kiekis serveriu
        int skaiciusServeriu = numObjects(pntr);
	if(skaiciusServeriu == -1){
		printf("ERROR: ieškodami skaičiaus objektų.");
		cJSON_Delete(pntr);
	       	return 1;	
	}
	// atminties priskirimas.
	requestInformacija* serveriai = malloc(sizeof (requestInformacija) * skaiciusServeriu);
	serveriai[i].serveris = malloc(sizeof(serverioInformacija));
	if (serveriai == NULL){
		cJSON_Delete(pntr);
		printf("ERROR01: nutiko klaida su atminties paskirmu.");
		return 1;
	}
	i= 0;
	//cJSON makro
	cJSON_ArrayForEach(iterator, pntr){

		cJSON *country = cJSON_GetObjectItemCaseSensitive(iterator, "country");
		cJSON *city = cJSON_GetObjectItemCaseSensitive(iterator, "city");
		cJSON *provider = cJSON_GetObjectItemCaseSensitive(iterator, "provider");
		cJSON *host = cJSON_GetObjectItemCaseSensitive(iterator, "host");
		cJSON *id = cJSON_GetObjectItemCaseSensitive(iterator, "id");
		
		if(country && cJSON_IsString(country)){
			strcpy(serveriai[i].serveris->country ,country->valuestring);
		}
                if(city && cJSON_IsString(city)){
                        strcpy(serveriai[i].serveris->city ,city->valuestring);
                }
                if(provider && cJSON_IsString(provider)){
                        strcpy(serveriai[i].serveris->provider ,provider->valuestring);
                }
                if(host && cJSON_IsString(host)){
                        strcpy(serveriai[i].serveris->host ,host->valuestring);
		}
               
                if(id && cJSON_isNumber(id)){
                        strcpy(serveriai[i].serveris->id ,id->valueint);
                }
		i++;
	}

	//"country":"Zambia","city":"Lusaka","provider":"Airtel","host":"speed.airtelntc.co.zm:8080","id":3686		

        printf("\n skaicius objektu: %d \n", skaiciusServeriu);



        return 0;
}
