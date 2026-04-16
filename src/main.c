/* Trumpas komentaras:
 * Programa matuoja atsisiuntimo ir persiuntimo greiti per HTTP užklausas į Ookla speedtest serverius.
 * Dauguma serverių grąžina HTTP 500 arba tuščią atsakymą į paprastą GET užklausą, nes jie reikalauja
 * specifinių endpoint'ų bent jau kaip suprantu. Kai kurie domenai visiškai nepasiekiami.
 * Mano programa pagrine gali greitčiau išmatuoti susisiekimo greitį su serveriu.
 */
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
	initialiseCurl();
	//  -a - visi moduliai integruoti.
	//  -du - atsisiuntimo greicio matuoklis, parsiuntimo greicio matuoklis 
	//  -s geriausias serveris.
	//  
	//  veiks kaip moduliai, bus skirting moduliai ir naudotojas gali pasimiti iki 3 moduliu, 
	
	//flags..
	  bool a = false;
        bool du = false;
        bool s = false;

        // flags
        for (int f = 1; f < argc; f++){
                if (strcmp(argv[f], "-a") == 0)  a  = true;
                if (strcmp(argv[f], "-du") == 0) du = true;
                if (strcmp(argv[f], "-s") == 0)  s  = true;
        }

        int i;
        cJSON* iterator = NULL;
        fflush(stdout);
        char* buff = readData();
        if (buff == NULL) return 1;

        cJSON* pntr = parseJSON(buff);
        if (pntr == NULL){
                printf("ERROR: nutiko klaida apdorojant JSON failą.");
                return 1;
        }
        free(buff);
        buff = NULL;

        int skaiciusServeriu = numObjects(pntr);
        if(skaiciusServeriu == -1){
                printf("ERROR: ieškodami skaičiaus objektų.");
                cJSON_Delete(pntr);
                return 1;
        }

        requestInformacija* serveriai = malloc(sizeof(requestInformacija) * skaiciusServeriu);
        if (serveriai == NULL){
                cJSON_Delete(pntr);
                printf("ERROR01: nutiko klaida su atminties paskirmu.");
                return 1;
        }

        i = 0;
        cJSON_ArrayForEach(iterator, pntr){
                cJSON *country  = cJSON_GetObjectItemCaseSensitive(iterator, "country");
                cJSON *city     = cJSON_GetObjectItemCaseSensitive(iterator, "city");
                cJSON *provider = cJSON_GetObjectItemCaseSensitive(iterator, "provider");
                cJSON *host     = cJSON_GetObjectItemCaseSensitive(iterator, "host");
                cJSON *id       = cJSON_GetObjectItemCaseSensitive(iterator, "id");

                if (country && cJSON_IsString(country) && country->valuestring != NULL)
                        strcpy(serveriai[i].serveris.country, country->valuestring);
                if (city && cJSON_IsString(city))
                        strcpy(serveriai[i].serveris.city, city->valuestring);
                if (provider && cJSON_IsString(provider))
                        strcpy(serveriai[i].serveris.provider, provider->valuestring);
                if (host && cJSON_IsString(host))
                        snprintf(serveriai[i].serveris.host, 100, "http://%s", host->valuestring);
                if (id && cJSON_IsNumber(id))
                        serveriai[i].serveris.id = id->valueint;
                i++;
        }

        CURL* handle1 = getHandle();
        char* salis = getCountry(handle1);
        if (salis != NULL)
                printf("Programa yra vykdoma is salies: %s \n\n", salis);

        // -s rezimas: randa greiciausia serveri
        if (s){
                printf("Ieškomas geriausias serveris...\n\n");
                int bestIndex = -1;
                double bestSpeed = -1.0;
                for (int x = 0; x < skaiciusServeriu; x++){
                        CURL* handle = getHandle();
                        int val = makeRequest(handle, &serveriai[x]);
                        if (val != 0) continue;
                        if (serveriai[x].downloadSpeed > bestSpeed){
                                bestSpeed = serveriai[x].downloadSpeed;
                                bestIndex = x;
                        }
                }
                if (bestIndex >= 0){
                        printf("Geriausias serveris: %s\n", serveriai[bestIndex].serveris.host);
                        printf("Šalis: %s, Miestas: %s\n", serveriai[bestIndex].serveris.country, serveriai[bestIndex].serveris.city);
                        printf("Atsisiuntimo greitis: %f Mbps\n", serveriai[bestIndex].downloadSpeed);
                } else {
                        printf("Nepavyko rasti veikiančio serverio.\n");
                }
                goto cleanup;
        }

        // -a or -du rezimas, testuoja visus serverius
        for (int x = 0; x < skaiciusServeriu; x++){
                CURL* handle = getHandle();
                int val = makeRequest(handle, &serveriai[x]);

                if (val != 0){
                        if (du || a)
                                printf("Cannot connect to the server: %s\n\n", serveriai[x].serveris.host);
                        continue;
                }

                if (du || a){
                        printf("\nPrisijungimas prie domeno : %s\n", serveriai[x].serveris.host);
                        printf("Domeno serveris yra randamas: %s, %s\n", serveriai[x].serveris.country, serveriai[x].serveris.city);
                        printf("Atsisiusta: %" CURL_FORMAT_CURL_OFF_T " megabitu, \nissiusta: %" CURL_FORMAT_CURL_OFF_T " megabitu.\n", serveriai[x].downloadedMegaBits, serveriai[x].uploadedMegaBits);
                        printf("Atsisiuntimo greitis: %f Mbps\n", serveriai[x].downloadSpeed);
                        printf("Persiuntimo greitis:  %f Mbps\n", serveriai[x].uploadSpeed);
                        printf("Laikas: %f s\n", serveriai[x].timeTaken);
                }

                // -a spausdina provideri
                if (a)
                        printf("Tiekėjas: %s\n", serveriai[x].serveris.provider);
        	}

cleanup:
        curl_global_cleanup();
        cJSON_Delete(pntr);
        free(serveriai);
        free(salis);
        return 0;
}
