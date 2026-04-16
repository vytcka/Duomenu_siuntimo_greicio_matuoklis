#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "requestInfo.h" 

#define LOCATION "../speedtest_server_list.json"


char* readData(){
	FILE* ftptr = fopen( "../speedtest_server_list.json", "r");
	if (ftptr == NULL){
		return NULL;
	}
	char* DATA = malloc(10000000);
	if (DATA == NULL){
		return NULL;
	}
	size_t sizeVar = 1000000;
	size_t bytesRead = fread(DATA, 1, sizeVar, ftptr);
	DATA[bytesRead] = '\0';
	fclose(ftptr);
	return DATA;
}

cJSON* parseJSON(char* pntr){
	if(pntr == NULL){ 
		printf("checking");
		return NULL;
	}
	cJSON* json = cJSON_Parse(pntr);
	if(json == NULL){
		const char* error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL){
			printf("Error: %s \n",error_ptr);
		}
		cJSON_Delete(json);
		return NULL;
	}
	return json;
}

int numObjects(cJSON* obj){
	if (obj == NULL){
		return -1;
	}
	return cJSON_GetArraySize(obj);

}
