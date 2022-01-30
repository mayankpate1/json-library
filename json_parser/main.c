/*
json parser lite

Mayank Patel
email:mayankpatel468@gmail.com
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"


int main()
{
    // ---------- parse packet -----------
    char json_string[] = "{\"val1\":\"11\",\"val2\":\"22\",\"val3\":\"33\"}";
    char MyVal[255];

    if(json_parse(json_string) == JSON_OK)
    {
        json_getStrValue(json_string,"val1",MyVal);
        printf(MyVal);
    }

    //----------- assemble a new packet---
    JSON_OBJECT jsonObject;
    char *jsonPacket;
    jsonObject = json_create(255); // create json
    json_addStrParameter(jsonObject,"val1","22"); // add parameters to json
    json_addStrParameter(jsonObject,"val2","11");
    json_addStrParameter(jsonObject,"val3","899089832");
    json_addIntParameter(jsonObject,"val5",20);
    json_addIntParameter(jsonObject,"val6",-3);
    json_addBoolParameter(jsonObject,"val7",true);
    jsonPacket = json_getPacket(jsonObject); // get assembled packet
    printf(jsonPacket); // print packet
    json_dump(jsonObject); // dump json


    printf("\n\n over..\n");
    return 0;
}
