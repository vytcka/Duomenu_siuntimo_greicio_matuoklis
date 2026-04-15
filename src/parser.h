#ifndef PARSER_H
#define PARSER_H

#include <cjson/cJSON.h>

#define LOCATION "../speedtest_server_list.json"

int readData();

cJSON* parseJSON();

#endif
