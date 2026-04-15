#include "requestInfo.h"
#include "parser.h"
#include "process.h"
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdio.h>


void downloadTest(CURL* handle){

}


int main(int argc, char** argv){
	//  -a - automatizuotas testas, viskas integruota, lokacija programos naudojimo
	//  -d - download testas
	//  -u - upload test
	//  -s find best server.
	//  -l location
	int i;
	printf("argc = %d\n", argc);

	for (i = 0; i<argc; i++){
		puts(argv[i]);
	}
	
	

	return 1;

}
