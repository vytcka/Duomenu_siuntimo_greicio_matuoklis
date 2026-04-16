#include "requestInfo.h"
#include "parser.h"
#include "process.h"
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



int main(int argc, char** argv){
	//  -a - visi moduliai integruoti.
	//  -du - atsisiuntimo greicio matuoklis, parsiuntimo greicio matuoklis 
	//  -s geriausias serveris.
	//  
	//  veiks kaip moduliai, bus skirting moduliai ir naudotojas gali pasimiti iki 3 moduliu, 
	
	//flags...
	bool a = false;
	bool du = false;
	bool s = false;
	int i;
	cJSON* iterator = NULL;
	printf("hello world\n");
	printf("argc = %d\n", argc);
	//Json failas perskaitomas
	printf("MADE IT TILL HERE1\n");
	fflush(stdout);
        char* buff = readData();
	
	if (buff ==NULL){
		return 1;
	}
	printf("\n made it till here!!! \n ");
	fflush(stdout);
	// convertuojamas i cJSON objekta.
        cJSON* pntr = parseJSON(buff);
	if (pntr == NULL){
		printf("ERROR: nutiko klaida apdorojant JSON failą.");
		return 1;
	}
	printf("checking");
	free(buff);
	buff = NULL;
	// gaunamas kiekis serveriu
	printf("MADE IT TILL HERE2");
        int skaiciusServeriu = numObjects(pntr);
	if(skaiciusServeriu == -1){
		printf("ERROR: ieškodami skaičiaus objektų.");
		cJSON_Delete(pntr);
	       	return 1;	
	}
	// atminties priskirimas.
	requestInformacija* serveriai = malloc(sizeof (requestInformacija) * skaiciusServeriu);
	if (serveriai == NULL){
		cJSON_Delete(pntr);
		printf("ERROR01: nutiko klaida su atminties paskirmu.");
		return 1;
	}
	printf("MADE IT TILL HERE3");
	i= 0;
	//cJSON makro
	cJSON_ArrayForEach(iterator, pntr){

		cJSON *country = cJSON_GetObjectItemCaseSensitive(iterator, "country");
		cJSON *city = cJSON_GetObjectItemCaseSensitive(iterator, "city");
		cJSON *provider = cJSON_GetObjectItemCaseSensitive(iterator, "provider");
		cJSON *host = cJSON_GetObjectItemCaseSensitive(iterator, "host");
		cJSON *id = cJSON_GetObjectItemCaseSensitive(iterator, "id");
		
		if (country && cJSON_IsString(country) && (country->valuestring != NULL)) {
    			strncpy(serveriai[i].serveris.country, country->valuestring, 99);
    			serveriai[i].serveris.country[99] = '\0';
}
                if(city && cJSON_IsString(city)){
                        strcpy(serveriai[i].serveris.city ,city->valuestring);
			serveriai[i].serveris.city[99] = '\0';
                }
                if(provider && cJSON_IsString(provider)){
                        strcpy(serveriai[i].serveris.provider ,provider->valuestring);
			serveriai[i].serveris.provider[99] = '\0';
                }
                if(host && cJSON_IsString(host)){
                        strcpy(serveriai[i].serveris.host ,host->valuestring);
			
		}
               
                if(id && cJSON_IsNumber(id)){
                        serveriai[i].serveris.id =id->valueint;
                }
		i++;
	}
	
	CURL* handle = getHandle();

	char* salis = getCountry(handle);
	if (salis != NULL){
	printf("Programa yra vykdoma is salies: %s", salis);
	}

	int val = makeRequest(handle, &serveriai[0]);
	

	printf("Prisijungimas prie domeno : %s", serveriai[0].serveris.host);
	printf("Domeno serveris yra randamas: %s, %s", serveriai[0].serveris.country ,serveriai[0].serveris.city);
	printf("Atsisiusta: %"CURL_FORMAT_CURL_OFF_T" megabitu, \n \
			issiusta: % "CURL_FORMAT_CURL_OFF_T " megabitu.", serveriai[0].downloadedMegaBits, serveriai[0].uploadedMegaBits);
	printf("vidutinis atsiuuntimo greitis: %f, \n  vidutinis persiuntimo greitis %f", serveriai[0].downloadSpeed, serveriai[0].uploadSpeed);
	printf("Laiko uztruko atlikti requesta: %f", serveriai[0].timeTaken);
	


	//"country":"Zambia","city":"Lusaka","provider":"Airtel","host":"speed.airtelntc.co.zm:8080","id":3686		
	
	cJSON_Delete(pntr);
	free(serveriai);
        return 0;
}
