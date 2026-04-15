#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

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
	size_t sizeVar = 10000000;
	size_t bytesRead = fread(DATA, 1, sizeVar, ftptr);
	printf("%s", DATA);
	printf("\n\n Kiekis baitu perskaityta. %zu\n \n", bytesRead);
	fclose(ftptr);
	return DATA;
}

cJSON* parseJSON(char* pntr){
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




int main(){	
	char* pntr = readData();
	cJSON* var = parseJSON(pntr);
	if (var == NULL){
		return 1;
	}
	char* string = cJSON_Print(var);
	printf("%s \n \n ", string);
	cJSON_Delete(var);
	free(string);
	free(pntr);
	return 0;
}




