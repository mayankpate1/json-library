/*
json parser lite

Mayank Patel
email:mayankpatel468@gmail.com
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "json.h"

static char *jsonString;

//----------------------- utils -------------------------------------------------
static void StringReplace(char *string,char replaceof,char replace)
{

  	int i, len, j;
    if(replace == NULL)
    {
        len = strlen(string);
        for(i = 0; i < len; i++)
        {
            if(string[i] == replaceof)
            {
                for(j = i; j < len; j++)
                {
                    string[j] = string[j + 1];
                }
                len--;
                i--;
            }
        }
    }
    else
    {
       for(int i = 0; i < strlen(string); i++){
        if(string[i] == replaceof)
            string[i] = replace;
        }

    }

}



//------------------------ Json Parser ------------------------------------------
static void json_removeInvertedComma(char* str,char *out)
{
    char* ptr;
    ptr = strchr(str,'\"');
    ptr++;
    strcpy(out,ptr);
    ptr = strchr(out,'\"');
    *ptr=0;
}
static void json_extractKeyAndValue(char *subStr,char *key,char *value)
{
    static char* ptr;
    static char buffer[255];

    strcpy(buffer,subStr);
    ptr = strchr(buffer,':');
    ptr++;
    json_removeInvertedComma(ptr,value);
    ptr--;
    *ptr=0;
    json_removeInvertedComma(buffer,key);

}

enum JSON_RESULT json_parse(char*json)
{
    enum JSON_RESULT status;
    StringReplace(json,' ',NULL);
    StringReplace(json,'\n',NULL);
    StringReplace(json,'\r',NULL);
    status = JSON_OK;
    char *ptr;
    char CurlyBracket_openCount=0,CurlyBracket_closeCount=0,colonCount=0,commaCount=0,quote_count=0;
    //printf(json);
    while(*json != NULL)
    {
        //printf(json);


        if(*json == '{') CurlyBracket_openCount++;
        if(*json == '}') CurlyBracket_closeCount++;

        if(*json == '\"') quote_count++;
        if(*json == ':') colonCount++;

        if(*json == ',')
        {
            commaCount++;
            if((quote_count %2) != 0)
            {
                status = JSON_INVALID_QUOTE;
                break;
            }


        }


        json++;

    }
    /*
    printf("colon:%d\n",colonCount);
    printf("comma:%d\n",commaCount);
    printf("quote_count:%d\n",quote_count);
    printf("CurlyBracket_openCount:%d\n",CurlyBracket_openCount);
    printf("CurlyBracket_closeCount:%d\n",CurlyBracket_closeCount);
    */
    if(colonCount != commaCount+1)
        status = JSON_MISSING_SEPARATORS;

    if(CurlyBracket_openCount != CurlyBracket_closeCount)
        status = JSON_CURLY_BRACKET_ERR;

    if((quote_count %2) != 0)
        status = JSON_INVALID_QUOTE;

    return status;
}


static char key[255],value[255];

void json_getStrValue(char*json,char *userkey,char*userValue)
{
    // remove braces
    char *ptr;
    ptr = strchr(json,'{');
    ptr++;
    strcpy(json,ptr);

    ptr = strchr(json,'}');
    *ptr =0;

    char *token;
    /* get the first token */
    token = strtok(json,",");
    /* walk through other tokens */
    while(token != NULL )
    {
        json_extractKeyAndValue(token,key,value);

        //printf("userKey:%s\n",userkey);
        //printf("key:%s\n",key);
        if(!strcmp(key,userkey))
        {
            strcpy(userValue,value);
            //printf("user key matched");
            break;
        }

        token = strtok(NULL,",");

        //break;
    }

}


//------------------------ Json Parser - end ------------------------------------------
//------------------------ Json Parser - assemble -------------------------------------


JSON_OBJECT json_create(int MaxLen)
{
    char* ptr;
    ptr = (char*)malloc(MaxLen * sizeof(char));
    strcpy(ptr,"{");

    return ptr;
}

/*
add string parameter to a json packet
*/
void json_addStrParameter(JSON_OBJECT json_obj,char* key,char* value)
{
    unsigned char tmpBuffer[255];
    tmpBuffer[0] = 0;

    strcpy(tmpBuffer,"\"");
    strcat(tmpBuffer,key);
    strcat(tmpBuffer,"\"");
    strcat(tmpBuffer,":");
    strcat(tmpBuffer,"\"");
    strcat(tmpBuffer,value);
    strcat(tmpBuffer,"\"");

    int len = strlen(json_obj);
    if(len > 1) strcat(json_obj,",");

    strcat(json_obj,tmpBuffer);
}
/*
add integer parameter to a json packet
*/

void json_addIntParameter(JSON_OBJECT json_obj,char* key,int value)
{
    unsigned char tmpBuffer[255],smallBuff[30];
    tmpBuffer[0] = 0;

    strcpy(tmpBuffer,"\"");
    strcat(tmpBuffer,key);
    strcat(tmpBuffer,"\"");
    strcat(tmpBuffer,":");
    //strcat(tmpBuffer,"\"");
    sprintf(smallBuff,"%d",value);
    strcat(tmpBuffer,smallBuff);
    //strcat(tmpBuffer,"\"");

    int len = strlen(json_obj);
    if(len > 1) strcat(json_obj,",");

    strcat(json_obj,tmpBuffer);
}

void json_addBoolParameter(JSON_OBJECT json_obj,char* key,bool value)
{
    unsigned char tmpBuffer[255],smallBuff[30];
    tmpBuffer[0] = 0;

    strcpy(tmpBuffer,"\"");
    strcat(tmpBuffer,key);
    strcat(tmpBuffer,"\"");
    strcat(tmpBuffer,":");
    //strcat(tmpBuffer,"\"");
    if(value == true) strcat(tmpBuffer,"true");
    else strcat(tmpBuffer,"false");
    //sprintf(smallBuff,"%d",value);
    //strcat(tmpBuffer,smallBuff);
    //strcat(tmpBuffer,"\"");

    int len = strlen(json_obj);
    if(len > 1) strcat(json_obj,",");

    strcat(json_obj,tmpBuffer);
}

char* json_getPacket(JSON_OBJECT json_obj)
{
    strcat(json_obj,"}");
    //printf(json_obj);
    return json_obj;
}

void json_dump(JSON_OBJECT json_obj)
{
    free(json_obj);
}
