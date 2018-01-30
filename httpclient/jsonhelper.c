#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json/json.h>

/*Parsing the json object*/
void json_parse(json_object *jobj) {
    
    enum json_type type;
    json_object *returnObject;
    
    /*Passing through every array element*/
    json_object_object_foreach(jobj, key, val) { 
    
        type = json_object_get_type(val);

        switch (type) {
            case json_type_boolean: 
                printf("%s: %s\n", key, json_object_get_boolean(val)? "true": "false");
                break;
            case json_type_double: 
                printf("%s: %lf\n", key, json_object_get_double(val));
                break;
            case json_type_int: 
                printf("%s: %d\n", key, json_object_get_int(val));
                break;
            case json_type_string: 
                printf("%s: %s\n", key, json_object_get_string(val));
                break;
            case json_type_array: 
                printf("%s: %s\n", key, "Array Value");
                // json_parse_array(jobj, key);
                break;
            case json_type_object:
                if (json_object_object_get_ex(jobj, key, &returnObject)) {
                    if ( !strcmp(json_object_to_json_string(returnObject), "{ }")) {
                        printf("%s: %s\n", key, "{ }");
                    } else {
                        json_parse(returnObject);
                    }
                } else {
                    printf("could not extrct json object value");
                }
                break;
            default:
                printf("not matchs\n");
                break;
        }

    }   

}

