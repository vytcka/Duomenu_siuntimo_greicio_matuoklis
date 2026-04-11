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
	size_t bytesRead = fread(DATA, 1, 10000000, ftptr);
	printf("%s", DATA);
	printf("\n\n Kiekis baitu perskaityta. %zu\n \n", bytesRead);
	fclose(ftptr);
	return 0;
}


int main(){
	readData();
	return 0;
}




