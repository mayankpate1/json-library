# json parser lite

The code is developed in Codeblocks IDE in C language. It provides necessary features of json to a user.

Its quit easy to assemble a json packet as you can see below 


    JSON_OBJECT jsonObject; // create object
    char *jsonPacket;
    jsonObject = json_create(255); // maximum size of your packet 
    json_addStrParameter(jsonObject,"val1","22"); // add parameters to json
    json_addStrParameter(jsonObject,"val2","11");
    json_addStrParameter(jsonObject,"val3","899089832");
    json_addIntParameter(jsonObject,"val5",20);
    json_addIntParameter(jsonObject,"val6",-3);
    json_addBoolParameter(jsonObject,"val7",true);
    jsonPacket = json_getPacket(jsonObject); // get assembled packet
    printf(jsonPacket); // print packet
    json_dump(jsonObject); // dump json

To parse the packet below code can be used 
    
    char json_string[] = "{\"val1\":\"11\",\"val2\":\"22\",\"val3\":\"33\"}"; // Json string 
    char MyVal[255];

    if(json_parse(json_string) == JSON_OK) // check if its valid 
    {
      
        json_getStrValue(json_string,"val1",MyVal); 
        printf(MyVal);
    }

    
user can call " json_getStrValue(json_string,"val1",MyVal); " function to get a string value. It only requires a "key" as an argument and the buffer in which 
the value is to be returned.

for any questions and queries, email me at mayankpatel468@gmail.com







