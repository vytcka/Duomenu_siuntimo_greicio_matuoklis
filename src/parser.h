#ifndef PARSER_H
#define PARSER_H

#include <cjson/cJSON.h>

#define LOCATION "../speedtest_server_list.json"

char* readData();

cJSON* parseJSON();

int numObjects(cJSON* obj);

#endif
