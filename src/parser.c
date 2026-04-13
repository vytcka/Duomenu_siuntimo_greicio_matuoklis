#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#define LOCATION "../speedtest_server_list.json"

char DATA[10000000];

int readData(){
	FILE* ftptr = fopen(LOCATION, "r");
	if (ftptr == NULL){
		return -1;
	}
	size_t bytesRead = fread(DATA, 1, sizeof DATA, ftptr);
	printf("%s", DATA);
	printf("\n\n Kiekis baitu perskaityta. %zu\n \n", bytesRead);
	fclose(ftptr);
	return 0;
}

cJSON* parseJSON(){
	cJSON* json = cJSON_Parse(DATA);
	if(json == NULL){
		const char* error_ptr = cJSON_GetErrorPtr();
		if (error_ptr == NULL){
			printf("Error: %s \n",error_ptr);
		}
		cJSON_Delete(json);
		return NULL;
	}
	return json;
}




int main(){	
	readData();
	cJSON* var = parseJSON();
	if (var == NULL){
		return 1;
	}
	char* string = cJSON_Print(var);
	printf("%s \n \n ", string);
	cJSON_Delete(var);
	free(string);
	return 0;
}




