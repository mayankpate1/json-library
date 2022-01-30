#include <stdbool.h>

typedef char* JSON_OBJECT;

enum JSON_RESULT{
    JSON_OK=0,
    JSON_ERR=1,
    JSON_INVALID_QUOTE=2,
    JSON_CURLY_BRACKET_ERR=3,
    JSON_MISSING_SEPARATORS=4
};

extern enum JSON_RESULT json_parse(char*json);
extern void json_getStrValue(char*json,char *userkey,char*userValue);
extern JSON_OBJECT json_create(int MaxLen);
extern void json_addStrParameter(JSON_OBJECT json_obj,char* key,char* value);
extern void json_addIntParameter(JSON_OBJECT json_obj,char* key,int value);
extern void json_addBoolParameter(JSON_OBJECT json_obj,char* key,bool value);
extern char* json_getPacket(JSON_OBJECT json_obj);
extern void json_dump(JSON_OBJECT json_obj);


